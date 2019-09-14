require "test/unit"
require "fileutils"

require_relative "shared"


class TestNm < Test::Unit::TestCase
	class << self
		def startup
			Shared.startup()
		end

		def shutdown
			Shared.shutdown()
		end
	end

	FT_NM = ENV['FT_NM'] || './build/ft_nm'

    # Wrapping function that make diff of two calls (equivalent of diff <(cmd_1) <(cmd_2))
    def diff(cmd_1, cmd_2)
       	out_1, err_1, code_1 = Shared.pipe(cmd_1)
       	out_2, err_2, code_2 = Shared.pipe(cmd_2)

       	# Substract /path/to/nm part of stderr
  		err_1 = err_1.sub /^\/.*\/nm:/, '' if err_1 
       	err_2 = err_2.sub /^\/.*\_nm:/, '' if err_2 

		assert_equal(err_1, err_2)
		assert_equal(out_1, out_2)
   	   	#assert_equal(code_1, code_2)
   	end

	#
	# Tests
	#

	def test_forbidden_functions
		out = Shared.pipe("nm #{FT_NM}").join('')

		forbidden = [
			'U _printf',
			'U _sprintf',
			'U _fprintf',
			'U _fopen',
			'U _exit',
			'U _memcmp',
			'U _memcpy',
			'U _strcmp',
			'U _strlen',			
			'U _dprintf',
		].map { |x| assert_not_match(/#{x}/, out, "Forbidden function #{x} into nm binary") }
	end

	def test_no_file
		diff("nm", "#{FT_NM}")
	end

	def test_simple
		file = Dir["#{__dir__}/samples/*.out"][0]
		diff("nm #{file}", "#{FT_NM} #{file}")
	end

	def test_on_dd
		diff("nm /bin/dd", "#{FT_NM} /bin/dd")
	end

	# This test is not triggered because the real nm loops on /dev/random
	#def test_on_dev_zero
	#	diff("nm /dev/zero", "#{FT_NM} /dev/zero")
	#end

	def test_on_dev_null
		diff("nm /dev/null", "#{FT_NM} /dev/null")
	end

	def test_on_dir
		diff("nm /usr", "#{FT_NM} /usr")
	end

	def test_simple_static_lib
		diff("nm /usr/lib/liby.a", "#{FT_NM} /usr/lib/liby.a")
	end

	def test_simple_binary
		diff("nm /sbin/reboot", "#{FT_NM} /sbin/reboot")
	end

	# Fail because of printing file name when the real nm on osx high sierra do not
	def test_multiple_valid_files
		files = "/usr/lib/libc.dylib /usr/lib/liby.a /bin/ps"
		diff("nm #{files}", "#{FT_NM} #{files}")
	end

	def test_multiple_valid_files_with_invalid
		files = "/usr/lib/libc.dylib #{__dir__}/nm.rb /usr/lib/liby.a /bin/ps"
		diff("nm #{files}", "#{FT_NM} #{files}")
	end

	def test_with_redirect
		diff("nm < /bin/dd", "#{FT_NM} < /bin/dd")
	end

	def test_systems_static_librarys
		samples = [
			'/usr/lib/libATCommandStudio.a',
			'/usr/lib/libkmodc++.a',
			'/usr/lib/libtclstub8.5.a',
			'/usr/lib/libpkstart.a',
			'/usr/lib/liby.a',
		].join(" ")
 		diff("nm #{samples}", "#{FT_NM} #{samples}")
	end

	# def test_corrupted_archives
	# 	corrupted_archives_samples = Dir["#{__dir__}/corrupted_samples/archives/*.a"].join(" ")
	# 	diff("nm #{corrupted_archives_samples}", "#{FT_NM} #{corrupted_archives_samples}")
	# end

	def test_empty_file
		file = "#{__dir__}/samples/empty.a"
		FileUtils.touch file
		diff("nm #{file}", "#{FT_NM} #{file}")
	end

	# This test is not triggered because the real nm loops on /dev/random
	#def test_on_dev_random
	#	diff("nm /dev/random", "#{FT_NM} /dev/random")
	#end

	def test_on_text_file
		diff("nm #{__dir__}/nm.rb", "#{FT_NM} #{__dir__}/nm.rb")
	end

	def test_on_tty
		diff("nm /dev/ttyw0", "#{FT_NM} /dev/ttyw0")
	end

	def test_no_read_rights
		file = "#{__dir__}/samples/to_remove.o"
		FileUtils.touch file
		FileUtils.chmod("-r", file)
		diff("nm #{file}", "#{FT_NM} #{file}")
		FileUtils.chmod("+r", file)
	end
end

