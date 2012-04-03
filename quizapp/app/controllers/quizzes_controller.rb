class QuizzesController < ApplicationController

  before_filter :setup
  before_filter :authenticate, :only => [:new, :edit, :update, :destroy]
  before_filter :correct_quiz, :only => [:edit, :destroy]

  def show
    @quiz = Quiz.find(params[:id])
    @title = "Quiz: " + @quiz.name
  end

  def new
    @quiz = Quiz.new
    @title = "New Quiz"
  end

  def edit
    @quiz = Quiz.find(params[:id])
  end

  def create
    @quiz = Quiz.new(params[:quiz])
    @quiz.course = @course

    if @quiz.save
      flash[:success] = "Quiz was successfully created."
      # Add processed questions
      add_questions(params[:questions])
      @title = "Quiz"
      redirect_to course_quiz_path(@course, @quiz)
    else
      flash.now[:error] = "Error while saving newly created quiz, check form fields."
      @title = "Quizzes"
      render :action => "new"
    end
  end

  def update

    if has_auth?(@course.user)
      @quiz = Quiz.find(params[:id])
      @quiz.course = @course
      @title = "Quiz: " + @quiz.name

      # Add processed questions
      add_questions(params[:questions])

      if @quiz.nil?
        flash.now[:error] = "Error encountered while updating the quiz."
        @title = "Edit Quiz"
        render :action => "edit"
      else
        if @quiz.update_attributes(params[:quiz])
          flash[:success] = "Quiz was successfully updated."
          redirect_to course_quiz_path(@course, @quiz)
        else
          flash.now[:warning] = "Form submission error, check all fields."
          @title = "Edit Quiz"
          render :action => "edit"
        end
      end
    else
      @quiz = Quiz.find(params[:id])

      for question in @quiz.questions
        submitted_answer = "q%s" % (question.id)
        @submission = Submission.where(:user_id => current_user.id, :question_id => question.id)[0]
        if @submission.nil?
          Submission.create(:answer => params[submitted_answer], :user_id => current_user.id, :question_id => question.id)
        else
          if not @submission.update_attributes(:answer => params[submitted_answer], :user_id => current_user.id, :question_id => question.id)
            flash.now[:error] = "Error while saving your quiz submission, report to admin."
            redirect_to course_path(@course)
          end
        end
      end

      flash[:success] = "Quiz submitted, watch your profile page for results!"
      redirect_to user_path(current_user)
    end
  end

  def destroy
    Quiz.find(params[:id]).destroy
    flash[:info] = "Quiz deleted."
    redirect_to course_path(@course)
  end

  private

    def setup
      @course = Course.find(params[:course_id])
    end

    def correct_quiz
      redirect_to(course_quizzes_path(@course), :notice => "Access Denied! You don't have the required authority.") unless has_auth?(@course.user)
    end

    def add_questions(questions)
      for question in questions.split("\r\n\r\n")
        block = question.split("\r\n")
        desc = block[0]
        opt1 = block[1]
        opt2 = block[2]
        opt3 = block[3]
        opt4 = block[4]
        ans = block[5]
        print desc, opt1, opt2, opt3, opt4, ans
        Question.create(:description => desc, :choice1 => opt1, :choice2 => opt2, :choice3 => opt3, :choice4 => opt4, :answer => ans, :quiz_id => @quiz.id)
      end
    end
end
