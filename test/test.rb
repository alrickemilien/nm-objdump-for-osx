require "test/unit"
require 'open3'

def pipe(cmd, options = [])
	data = {}
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
		return data[:out], data[:err]
	end
end

class TestSimpleNumber < Test::Unit::TestCase
  def test_simple
	print pipe('echo "Salut"')
  end
end

