# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rake db:seed (or created alongside the db with db:setup).
#
# Examples:
#
#   cities = City.create([{ :name => 'Chicago' }, { :name => 'Copenhagen' }])
#   Mayor.create(:name => 'Daley', :city => cities.first)

User.create(:name => 'QuizApp Admin',   :password => 'admin',  :email => 'admin@quiz.app', :role => 'admin',               :about => "The Admin")
User.create(:name => 'Nidhi Gupta',     :password => 'nidhi',  :email => 'soni.nini@gmail.com', :role => 'student',        :about => "07020001")
User.create(:name => 'Ajay Chhatwal',   :password => 'ajay',   :email => 'ajay.charlie@gmail.com', :role => 'student',     :about => "07020002")
User.create(:name => 'Rohit Yadav',     :password => 'rohit',  :email => 'rohityadav89@gmail.com', :role => 'student',     :about => "07020003")
User.create(:name => 'SabyaSachi',      :password => 'sachi',  :email => 'sachi1325@gmail.com', :role => 'student',        :about => "07020004")
User.create(:name => 'Saket Jalan',     :password => 'saket',  :email => 'saaketjalan@gmail.com', :role => 'student',      :about => "07020006")
User.create(:name => 'Rahul Jain',      :password => 'rahul',  :email => 'rahuljain.roy@gmail.com', :role => 'student',    :about => "07020007")
User.create(:name => 'Nitin Yadav',     :password => 'nitin',  :email => 'nitinnitin18@gmail.com', :role => 'student',     :about => "07020008")
User.create(:name => 'Lavanya',         :password => 'vanya',  :email => 'lavanya@gmail.com', :role => 'student',          :about => "07020009")
User.create(:name => 'Divakar Bari',    :password => 'divx',   :email => 'alkatraz13@gmail.com', :role => 'student',       :about => "07020010")
User.create(:name => 'Himanshu Singh',  :password => 'manshu', :email => 'hs.thegreat@gmail.com', :role => 'student',      :about => "07020011")
User.create(:name => 'Ankit Choudhary', :password => 'ankit',  :email => 'ankit.goaldecided@gmail.com', :role => 'student',:about => "07020012")
