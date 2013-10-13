require 'csv'

filename = ARGV[0]
sum = {}
deb = []
i = 0
all = 0

CSV.foreach(filename) do |row|
	if row[4] =~ /[A-Z]+/
		deb << row[4].split(" ")[0].to_s
		deb[i] = deb[i].to_s
		if row[2] == nil
			row[2] = 0
		end
		sum[deb[i]] = sum[deb[i]].to_i + row[2].to_i
		i += 1
	end
end


#sum = sum.sort
#puts sum

CSV.open(filename.gsub(".csv","") + "_results.csv", "w") do |csv|
	sum.to_a.each do |elem|
		csv << elem
	end
end
