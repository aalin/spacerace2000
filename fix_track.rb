positions = []

File.open("tracks/track01.old", 'r') do |f|
  f.each_line do |line|
    positions << line.split.map(&:to_f)
  end
end

positions.each do |x, y, z|
  z += rand(50.0)
  puts [x, y, z].join(" ")
end
