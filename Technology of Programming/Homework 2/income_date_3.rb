require "csv"

max_inc = 0.00
date = nil

CSV.foreach("bank.csv") do |row|
    if row[1].to_f > max_inc
    	max_inc = row[1].to_f
    	date = row[0].to_s
    end
end

	printf "%s", date
