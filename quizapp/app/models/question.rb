class Question < ActiveRecord::Base
  validates :description,  :presence => true
  validates :choice1,  :presence => true
  validates :choice2,  :presence => true
  validates :choice3,  :presence => true
  validates :choice4,  :presence => true
  validates :answer,  :presence => true
  has_many :submissions, :dependent => :destroy
  belongs_to :quiz
end
