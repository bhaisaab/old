class UsersController < ApplicationController

  before_filter :authenticate, :only => [:edit, :update, :destroy]
  before_filter :correct_user, :only => [:edit, :update, :destroy]

  def index
    @users = User.all
    @title = "Users"
  end

  def show
    @user = User.find(params[:id])
    @title = @user.name
  end

  def new
    @user = User.new
    @title = "Sign up"
  end

  def edit
    @user = User.find(params[:id])
    @title = "Settings"
  end

  def create
    @user = User.new(params[:user])
    @user.role = "student" # Set default, overide possible only by admins
    if @user.save
      sign_in @user
      flash[:success] = "Profile was successfully created."
      @title = "Sign in"
      redirect_to @user
    else
      flash.now[:error] = "Profile creation error, check form fields."
      @title = "Sign up"
      render :action => "new"
    end
  end

  def update
    @user = User.find(params[:id])
    @title = @user.name
    if @user.nil?
      flash.now[:error] = "Error encountered while updating your profile."
      @title = "Edit Profile"
      render :action => "edit"
    else
      if @user.update_attributes(params[:user])
        flash[:success] = "Profile was successfully updated."
        @title = @user.name
        redirect_to @user
      else
      flash.now[:warning] = "Form submission error, check all fields."
      @title = "Edit Profile"
      render :action => "edit"
      end
    end
  end

  def destroy
    User.find(params[:id]).destroy
    flash[:info] = "Account deleted."
    redirect_to users_path
  end

  private

    def correct_user
      @user = User.find(params[:id])
      redirect_to(users_path, :notice => "Access Denied! You don't have the required authority.") unless has_auth?(@user)
    end

end
