<?php
$plugin = array(
  'title' => t('CTools demos'),
  'description' => t('CTools demonstrations'),
  'content types' => 'ctools_demos_demos_ctools_content_types',
  'admin title' => 'ctools_demos_content_types_admin_title',
  'admin info' => 'ctools_demos_content_types_admin_info',
);

function ctools_demos_demos_ctools_content_types() {
  $plugins = array();
  $plugin = ctools_get_content_type('demos');
  foreach (ctools_demos_get_demos() as $demo) {
    $name = 'demo_'. $demo['name'];
//    $demo['single'] = TRUE;
    $demo['name'] = $name;
    $demo['title'] = t('CTools demo: @title', array('@title' => $demo['title'] ? $demo['title'] : ucfirst(str_replace('_', ' ', $demo['name']))));
    $demo['render callback'] = 'ctools_demos_content_types_render';
    $demo['admin title'] = 'ctools_demos_content_types_admin_title';
    $demo['admin info'] = 'ctools_demos_content_types_admin_info';
    $demo['path'] = $plugin['path'];
    $demo['file'] = $plugin['file'];
    
    $plugins[$name] = $demo;
  }
  return $plugins;
}

function ctools_demos_content_types_render($subtype, $conf, $args, $context) {
  zdpm($subtype, $conf, $args, $context);
  
  $block = new stdClass();
  
  $block->title = $subtype;
  
  return $block;
}

function ctools_demos_content_types_admin_title($name) {
  t('CTools demo: @title', array('@title' => ucfirst(str_replace('_', ' ', $name))));
}

function ctools_demos_content_types_admin_info($name) {
  $args = func_get_args();
//  zdpm($args);
  return $name;
}