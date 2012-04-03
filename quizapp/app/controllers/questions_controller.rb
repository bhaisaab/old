class QuestionsController < ApplicationController

  before_filter :setup
  before_filter :authenticate, :only => [:new, :edit, :update, :destroy]
  before_filter :correct_question, :only => [:edit, :update, :destroy]

  def index
    @questions = Question.where(:quiz_id => params[:quiz_id])
    @title = "Questions"
  end

  def show
    @question = Question.find(params[:id])
    @title = "Quiz: " + @quiz.name
  end

  def new
    @question = Question.new
    @title = "New Question"
  end

  def edit
    @question = Question.find(params[:id])
  end

  def create
    @question = Question.new(params[:question])
    @question.quiz = @quiz

    if @question.save
      flash[:success] = "Question was successfully created."
      @title = "Question"
      redirect_to course_quiz_question_path(@quiz.course, @quiz, @question)
    else
      flash.now[:error] = "Error while saving newly created question, check form fields."
      @title = "Questions"
      render :action => "new"
    end
  end

  def update
    @question = Question.find(params[:id])
    @question.quiz = @quiz
    @title = "Quiz: " + @quiz.name

    if @question.nil?
      flash.now[:error] = "Error encountered while updating the question."
      @title = "Edit Question"
      render :action => "edit"
    else
      if @question.update_attributes(params[:question])
        flash[:success] = "Question was successfully updated."
        redirect_to course_quiz_question_path(@quiz.course, @quiz, @question)
      else
        flash.now[:warning] = "Form submission error, check all fields."
        @title = "Edit Question"
        render :action => "edit"
      end
    end
  end

  def destroy
    Question.find(params[:id]).destroy
    flash[:info] = "Question deleted."
    redirect_to course_quiz_path(@quiz.course, @quiz)
  end

  private

    def setup
      @quiz = Quiz.find(params[:quiz_id])
    end

    def correct_question
      redirect_to(course_quiz_questions_path(@quiz.course, @quiz), :notice => "Access Denied! You don't have the required authority.") unless has_auth?(@quiz.course.user)
    end

end
