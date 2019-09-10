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
		puts data[:err]
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

class TestOtool < Test::Unit::TestCase
    class << self
		def startup
			shared.startup()
		end

		def shutdown
			shared.shutdown()
		end
	end

	#
	# Tests
	#

	def test_simple
		file = Dir["#{__dir__}/samples/*.out"][0]
		diff("otool -t #{file}", "./build/ft_otool #{file}")
	end

	def test_no_read_rights
		file = Dir["#{__dir__}/samples/*.out"][0]
        FileUtils.chmod("-r", file)
		diff("otool -t #{file}", "./build/ft_otool #{file}")
		FileUtils.chmod("+r", file)
		puts ret, err
	end
end

