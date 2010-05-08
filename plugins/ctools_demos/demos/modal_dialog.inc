<?php

$plugin  = array(
  'hook menu'       => 'ctools_demos_modal_dialog_menu',
  'description'     => t('Ideal for settings.'),
);

function ctools_demos_modal_dialog_menu($plugin) {
  $items = array();
  $items['ctools-demos/modal-dialog/%ctools_js/do'] = array(
    'page callback' => 'ctools_demos_modal_dialog_modal',
    'page arguments' => array(2),
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );
  return $items;
}

function ctools_demos_modal_dialog_ctools_demos_demos_render($plugin) {
  $output = '@todo';
  
  ctools_include('ajax');
  ctools_include('modal');
  
  $output = ctools_modal_text_button(t('I am a button!'), 'ctools-demos/modal-dialog/nojs/do', t('Alternate text'));
  return $output;
}

function ctools_demos_modal_dialog_modal($js = FALSE) {
  $output = '';
  $plugin = ctools_demos_demo_load('modal_dialog');
  $image_path = $plugin['path'] .'/demos-1.jpg';
  $output .= $image_path;
  $output .= theme('image', $image_path, t('Hello world!'));
  return $output;
}


