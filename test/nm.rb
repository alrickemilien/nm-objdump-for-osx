require "test/unit"
require 'open3'
require "fileutils"
require "shared"

class TestNm < Test::Unit::TestCase
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
		diff("nm #{file}", "./build/ft_nm #{file}")
	end

	def test_no_read_rights
		file = Dir["#{__dir__}/samples/*.out"][0]
		FileUtils.chmod("-r", file)
		ret, err = pipe("nm #{file}")
		FileUtils.chmod("+r", file)
		puts ret, err
	end
end

