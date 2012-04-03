class CoursesController < ApplicationController

  before_filter :authenticate, :only => [:new, :edit, :update, :destroy]
  before_filter :correct_course, :only => [:edit, :update, :destroy]

  def index
    @courses = Course.all
    @title = "Courses"
  end

  def show
    @course = Course.find(params[:id])
    @title = "Course: " + @course.name
  end

  def new
    @course = Course.new
    @title = "New Course"
  end

  def edit
    @course = Course.find(params[:id])
  end

  def create
    @course = Course.new(params[:course])
    @course.user = current_user
    if @course.save
      flash[:success] = "Course was successfully created."
      @title = "Course: " + @course.name
      redirect_to @course
    else
      flash.now[:error] = "Error while saving newly created course, check form fields."
      @title = "Courses"
      render :action => "new"
    end
  end

  def update
    @course = Course.find(params[:id])
    @title = "Course: " + @course.name

    # If user in not admin, maintain user id
    if not is_admin?(current_user)
      params[:course][:user_id] = @course.user.id
    end

    if @course.nil?
      flash.now[:error] = "Error encountered while updating the course."
      @title = "Edit Course"
      render :action => "edit"
    else
      if @course.update_attributes(params[:course])
        flash[:success] = "Course was successfully updated."
        @title = "Course: " + @course.name
        redirect_to @course
      else
      flash.now[:warning] = "Form submission error, check all fields."
      @title = "Edit Course"
      render :action => "edit"
      end
    end
  end

  def destroy
    Course.find(params[:id]).destroy
    flash[:info] = "Course deleted."
    redirect_to courses_path
  end

  private

    def correct_course
      @course = Course.find(params[:id])
      redirect_to(courses_path, :notice => "Access Denied! You don't have the required authority.") unless has_auth?(@course.user)
    end

end
