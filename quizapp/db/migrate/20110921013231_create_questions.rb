class CreateQuestions < ActiveRecord::Migration
  def self.up
    create_table :questions do |t|
      t.string :description
      t.string :choice1
      t.string :choice2
      t.string :choice3
      t.string :choice4
      t.integer :answer
      t.integer :quiz_id

      t.timestamps
    end
  end

  def self.down
    drop_table :questions
  end
end
