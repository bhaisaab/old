class CreateSubmissions < ActiveRecord::Migration
  def self.up
    create_table :submissions do |t|
      t.integer :answer
      t.integer :user_id
      t.integer :question_id

      t.timestamps
    end
  end

  def self.down
    drop_table :submissions
  end
end
