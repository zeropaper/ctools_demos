<?php

$plugin = array(
  'hook menu'       => 'ctools_demos_ajax_menu',
  'page callback'   => 'ctools_demos_ajax_page',
  'description'     => t('Demonstration of the AJAX responder capacities.'),
);

function ctools_demos_ajax_menu($plugin) {
  $hooks = array();
  
  $hooks['ctools-demos/ajax/page'] = array(
    'title'             => 'Ctools AJAX demo',
    'page callback'     => 'ctools_demos_ajax_page',
    'access arguments'  => array('access content'),
  );
  
  $hooks['ctools-demos/ajax/form'] = array(
    'title'             => 'Ctools AJAX demo',
    'page callback'     => 'drupal_get_form',
    'page arguments'    => array('ctools_demos_ajax_form'),
    'access arguments'  => array('access content'),
  );
  
  $hooks['ctools-demos/ajax/page/%ctools_js/do'] = array(
    'title'             => 'Ctools AJAX demo',
    'page callback'     => 'ctools_demos_ajax',
    'page arguments'    => array(2),
    'access arguments'  => array('access content'),
    'file path'         => $plugin['path'],
    'file'              => 'ajax.inc',
  );
  
  return $hooks;
}


function ctools_demos_ajax_page() {
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  
  
  
  $output = '';
  $output .= '<div>'. t('This is just a page callback for the ctools demonstration.') .'<br/>';
  $output .= t('More information: !link', array('!link' => l('http://zroger.com/node/30', 'http://zroger.com/node/30'))) .'</div>';
  
  
  $dest = 'ctools-demos/ajax/page/nojs/do';
  $output .= ctools_ajax_text_button(t('Hey! I am a button'), $dest, t('Alternate text'), 'ctools-ajax-demos-link');
  
  $plugin = ctools_demos_get_demo('ajax');
  drupal_add_js($plugin['path'] .'/ajax.js');
  
  return $output;
}



function ctools_demos_ajax($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    
    $output = t('This is the "ajax" content.');
    
    $output .= t('The "nojs" version of this content is available here') .': ctools-demos/ajax/page/nojs/do';
    
    // both methods miseravly #FAIL
    $plugin = ctools_demos_demo_load('ajax');
    $plugins = ctools_demos_get_demos();
    
    $image_path = drupal_get_path('module', 'ctools_demos') .'/plugins/ctools_demos/demos/demos-1.jpg';
    
    $output .= '<br/>'. theme('image', $image_path, t('Hello world!'));
    
    $commands = array();
    
//    $commands[] = ctools_demos_ajax_command_fade_out('.ctools-ajax-demos-link');
//    $commands[] = ctools_ajax_command_html('.ctools-ajax-demos-link', $output);
//    $commands[] = ctools_demos_ajax_command_fade_in('.ctools-ajax-demos-link');
    
    $commands[] = ctools_demos_ajax_effects_faded('.ctools-ajax-demos-link', $output);
    
    ctools_ajax_render($commands);
    // above command will exit().
  }
  else {
    return t('This is the "nojs" content.');
  }
}

function ctools_demos_ajax_effects_slided($selector, $html) {
  return ctools_demos_ajax_command_eval("
\$('$selector').slideUp('slow', function(){
  \$(this).html('". str_replace("'", "\\'", $html) ."').slideDown('slow');
})");
}

function ctools_demos_ajax_effects_faded($selector, $html) {
  return ctools_demos_ajax_command_eval("
\$('$selector').fadeOut('slow', function(){
  \$(this).html('". str_replace("'", "\\'", $html) ."').fadeIn('slow');
})");
}

function ctools_demos_ajax_command_fade_in($selector) {
  return array(
    'command' => 'fade_in',
    'selector' => $selector,
  );
}

function ctools_demos_ajax_command_fade_out($selector) {
  return array(
    'command' => 'fade_out',
    'selector' => $selector,
  );
}

function ctools_demos_ajax_command_zoom($selector) {
  return array(
    'command' => 'zoom',
    'selector' => $selector,
  );
}

function ctools_demos_ajax_command_eval($code) {
  return array(
    'command' => 'eval',
    'code' => $code,
  );
}


function ctools_demos_ajax_form(&$form_state) {
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  $form = array(
    'choice' => array(
      '#type' => 'select',
      '#title' => t('Choices'),
      '#options' => array(
        'kitty' => t('Hello'),
        'function' => t('form'),
        'boring' => t('example 1'),
        'very_boring' => t('example 2'),
      ),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    ),
  );
}