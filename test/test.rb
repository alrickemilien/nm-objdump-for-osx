require "test/unit"
require 'open3'
require "fileutils"

def pipe(cmd, options = [])
	data = {}
	puts cmd
	Open3.popen3(cmd) do |stdin, out, err, external|

	  # Create a thread to read from each stream
	  { :out => out, :err => err }.each do |key, stream|
	   	 Thread.new do
	    	  until (line = stream.gets).nil? do
	    	    data[key] = line
	    	  end
			end
	  	end
	  	# Don't exit until the external process is done
	  	external.join
		return data[:out], data[:err], external.value
	end
end

# Wrapping function that make diff of two calls (equivalent of diff <(cmd_1) <(cmd_2))
def diff(cmd_1, cmd_2)
	out_1, err_1, code_1 = pipe(cmd_1)
	out_2, err_2, code_2 = pipe(cmd_2)

	assert_equal(code_1, code_2)
	assert_equal(out_1, out_2)
	assert_equal(err_1, err_2)
end

class TestSimpleNumber < Test::Unit::TestCase
	def self.startup
		if ENV['CC'] == nil
			ENV['CC'] = 'clang'
		end

		if ENV['ASM'] == nil
			ENV['ASM'] = 'nasm'
		end

		@c_archs = [
			'arm-none-eabi',
			'armv7a-none-eabi',
			'arm-linux-gnueabihf',
			'arm-none-linux-gnueabi',
			'i386-pc-linux-gnu',
			'x86_64-apple-darwin10',
			'i686-w64-windows-gnu', # same as i686-w64-mingw32
			'x86_64-pc-linux-gnu', # from ubuntu 64 bit
			'x86_64-unknown-windows-cygnus', # cygwin 64-bit
			'x86_64-w64-windows-gnu', # same as x86_64-w64-mingw32
			'i686-pc-windows-gnu', # MSVC
			'x86_64-pc-windows-gnu', # MSVC 64-BIT
		]

		# .o
		@c_obj_samples = Dir["#{__dir__}/samples/*.lib.*.c"]
		@c_archs.each { |x| @c_obj_samples.each { |y| cmd = "#{ENV['CC']} -c #{y} -o #{y}.#{x}.o -arch #{x}"; pipe(cmd) } }

		# a.out
		@c_bin_samples = Dir["#{__dir__}/samples/*.out.c"]
		@c_archs.each { |x| @c_bin_samples.each { |y| cmd = "#{ENV['CC']} #{y} -o #{y}.#{x}.out -arch #{x}"; pipe(cmd) } }

		# .a
		@c_static_samples = Dir["#{__dir__}/samples/*.lib.*.o"]
		@c_archs.each { |x| @c_static_samples.each { |y| cmd = "ar rc #{y}.#{x}.a #{y}"; pipe(cmd) } }

		# .so
		@c_shared_samples = Dir["#{__dir__}/samples/*.lib.c"]
		@c_archs.each { |x| @c_shared_samples.each { |y| cmd = "#{ENV['CC']} #{y} -shared -o #{y}.#{x}.so -arch #{x}"; pipe(cmd) } }

		# .so with fPIC	
		@c_shared_samples = Dir["#{__dir__}/samples/*.lib.c"]
		@c_archs.each { |x| @c_shared_samples.each { |y| cmd = "#{ENV['CC']} #{y} -shared -fPIC -o #{y}.#{x}.pic.so -arch #{x}"; pipe(cmd) } }

		# .so with library dependancy
		@c_dependant_shared_samples = Dir["#{__dir__}/samples/*.lib.math.c"]
		@c_archs.each { |x| @c_dependant_shared_samples.each { |y| cmd = "#{ENV['CC']} #{y} -shared -o #{y}.#{x}.so -lm -arch #{x}"; pipe(cmd) } }

		# .so with library dependancy and fPIC
		@c_dependant_shared_samples = Dir["#{__dir__}/samples/*.lib.math.c"]
		@c_archs.each { |x| @c_dependant_shared_samples.each { |y| cmd = "#{ENV['CC']} #{y} -shared -fPIC -o #{y}.#{x}.pic.so -lm -arch #{x}"; pipe(cmd) } }

		# .o fat arch
		@c_shared_samples = Dir["#{__dir__}/samples/*.lib.c"]
		@c_shared_samples.each { |x| cmd = "#{ENV['CC']} #{x} -shared -o #{x}.fat.o -arch #{@c_archs.join(' -arch ')}"; pipe(cmd) }

		# .so fat arch
		@c_shared_samples = Dir["#{__dir__}/samples/*.lib.c"]
		@c_shared_samples.each { |x| cmd = "#{ENV['CC']} #{x} -shared -o #{x}.fat.so -arch #{@c_archs.join(' -arch ')}"; pipe(cmd) }

		@s_archs = [
			'bin',       # flat-form binary files (e.g. DOS .COM, .SYS)
			'ith',       # Intel hex
			'srec',      # Motorola S-records
			'aout',      # Linux a.out object files
			'aoutb',     # NetBSD/FreeBSD a.out object files
			'coff',      # COFF (i386) object files (e.g. DJGPP for DOS)
			'elf32',     # ELF32 (i386) object files (e.g. Linux)
			'elf64',     # ELF64 (x86_64) object files (e.g. Linux)
			'elfx32',    # ELFX32 (x86_64) object files (e.g. Linux)
			'as86',      # Linux as86 (bin86 version 0.3) object files
			'obj',       # MS-DOS 16-bit/32-bit OMF object files
			'win32',     # Microsoft Win32 (i386) object files
			'win64',     # Microsoft Win64 (x86-64) object files
			'rdf',       # Relocatable Dynamic Object File Format v2.0
			'ieee',      # IEEE-695 (LADsoft variant) object file format
			'macho32',   # NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (i386) object files
			'macho64',   # NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (x86_64) object files
			'dbg',       # Trace of all info passed to output stage
			'elf',       # ELF (short name for ELF32)
			'macho',     # MACHO (short name for MACHO32)
			'win',       # WIN (short name for WIN32)
		]
		
		# .s to .o
		@s_samples = Dir["#{__dir__}/samples/*.s"]
		# @s_archs.each { |x| @s_samples.each { |y| cmd = "#{ENV['ASM']} -f #{x} #{y} -o #{y}.#{x}.o"; pipe(cmd) } }
	end

	def teardown
		# @trash = Dir["#{__dir__}/samples/*.a", "#{__dir__}/samples/*.o", "#{__dir__}/samples/*.so", "#{__dir__}/samples/*.out"]
		# @trash.each { |y| cmd = "rm -rf #{y}"; puts cmd; pipe(cmd) }
	end

	#
	# Tests
	#

	def test_simple
		file = Dir["#{__dir__}/samples/*.out"][0]
		diff("nm #{file}", "./bin/ft_nm #{file}")
	end

	def test_no_read_rights
		file = Dir["#{__dir__}/samples/*.out"][0]
		FileUtils.chmod("-r", file)
		ret, err = pipe("nm #{file}")
		FileUtils.chmod("+r", file)
		puts ret, err
	end
end

