
Drupal = Drupal || {};
Drupal.CTools = Drupal.CTools || {};
Drupal.CTools.AJAX = Drupal.CTools.AJAX || {};
Drupal.CTools.AJAX.commands = Drupal.CTools.AJAX.commands || {};

Drupal.CTools.AJAX.commands.fade_in = function(data) {
  $(data.selector).fadeIn();
  Drupal.attachBehaviors($(data.selector));
};

Drupal.CTools.AJAX.commands.fade_out = function(data) {
  $(data.selector).fadeOut();
  Drupal.attachBehaviors($(data.selector));
};

Drupal.CTools.AJAX.commands.zoom = function(data) {
  $(data.selector).css('font-size', '120%');
  Drupal.attachBehaviors($(data.selector));
};

Drupal.CTools.AJAX.commands.eval = function(data) {
  eval(data.code);
};