$(document).ready(function(){
  $(".alert-message").alert()
  $("#userTable").tablesorter()

  $('a[data-method="delete"]').live('ajax:success', function(){});

});
