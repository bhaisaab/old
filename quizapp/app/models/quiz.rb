class Quiz < ActiveRecord::Base
  validates :name,  :presence => true
  has_many :questions, :dependent => :destroy
  belongs_to :course
end
