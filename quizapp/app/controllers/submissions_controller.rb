class SubmissionsController < ApplicationController

  before_filter :authenticate, :only => [:index, :destroy]
  before_filter :correct_user, :only => [:index, :destroy]

  def index
    @submissions = Submission.all
    respond_to do |format|
      format.html # index.html.erb
      format.json  { render :json => @submissions }
    end
  end

  def destroy
    @submission = Submission.find(params[:id])
    @submission.destroy
    respond_to do |format|
      format.html { redirect_to(submissions_url) }
      format.json  { head :ok }
    end
  end

  private

    def correct_user
      redirect_to("/", :notice => "Access Denied! You don't have the required authority.") unless is_admin?(current_user)
    end

end
