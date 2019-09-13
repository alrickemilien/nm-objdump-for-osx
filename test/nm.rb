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

    # Wrapping function that make diff of two calls (equivalent of diff <(cmd_1) <(cmd_2))
    def diff(cmd_1, cmd_2)
       	out_1, err_1, code_1 = Shared.pipe(cmd_1)
       	out_2, err_2, code_2 = Shared.pipe(cmd_2)

       	# Substract /path/to/nm part of stderr
  		err_1 = err_1.sub /^\/.*\/nm:/, '' if err_1 
       	err_2 = err_2.sub /^\/.*\/nm:/, '' if err_2 

   	   	assert_equal(code_1, code_2)
   	   	assert_equal(out_1, out_2)
   	   	assert_equal(err_1, err_2)
   	end

	#
	# Tests
	#

	def test_no_file
		diff("nm", "./build/ft_nm")
	end

	def test_simple
		file = Dir["#{__dir__}/samples/*.out"][0]
		diff("nm #{file}", "./build/ft_nm #{file}")
	end

	def test_on_dd
		diff("nm /bin/dd", "./build/ft_nm /bin/dd")
	end

	# This test is not triggered because the real nm loops on /dev/random
	#def test_on_dev_zero
	#	diff("nm /dev/zero", "./build/ft_nm /dev/zero")
	#end

	def test_on_dev_null
		diff("nm /dev/null", "./build/ft_nm /dev/null")
	end

	# This test is not triggered because the real nm loops on /dev/random
	#def test_on_dev_random
	#	diff("nm /dev/random", "./build/ft_nm /dev/random")
	#end

	def test_on_text_file
		diff("nm #{__dir__}/nm.rb", "./build/ft_nm #{__dir__}/nm.rb")
	end

	def test_no_read_rights
		file = "#{__dir__}/samples/to_remove.o"
		FileUtils.touch file
		FileUtils.chmod("-r", file)
		diff("nm #{file}", "./build/ft_nm #{file}")
		FileUtils.chmod("+r", file)
	end
end

