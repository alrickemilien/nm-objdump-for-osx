require "test/unit"
require "fileutils"

require_relative "shared"

class TestOtool < Test::Unit::TestCase
    class << self
		def startup
			Shared.startup()
		end

		def shutdown
			Shared.shutdown()
		end
	end

    # Wrapping function that make diff of two calls (equivalent of diff <(cmd_1) <(cmd_2))
    def diff(cmd_1, cmd_2)
		out_1, err_1, code_1 = Shared.pipe(cmd_1)
		out_2, err_2, code_2 = Shared.pipe(cmd_2)

		# Substract /path/to/nm part of stderr
	   	err_1 = err_1.sub /^\/.*\/otool:/, '' if err_1 
		err_2 = err_2.sub /^\/.*\_otool:/, '' if err_2 

	 	assert_equal(err_1, err_2)
	 	assert_equal(out_1, out_2)
		   #assert_equal(code_1, code_2)
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

