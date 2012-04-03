class Course < ActiveRecord::Base
  validates_uniqueness_of :name
  validates :name,  :presence => true
  has_many :quizzes, :dependent => :destroy
  belongs_to :user
end
