<?php

// Plugin definition
$plugin = array(
  'title' => t('Demos style'),
  'description' => t('A demonstration for the Panels styles plugins.'),
  'render pane' => 'ctools_demos_style_render_pane',
  'render panel' => 'ctools_demos_style_render_panel',
  'settings form' => 'ctools_demos_style_settings_form',
  'settings validate' => 'ctools_demos_style_settings_validate',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_ctools_demos_style_render_panel($display, $panel_id, $panes, $settings) {
  $output = '';
  
  if (in_array('argument_managed_page_1', array_keys($display->context))) {
    $has_page_context = TRUE;
  }
  foreach ($panes as $pane_id => $content) {
//    $output .= $has_page_context ? '<div id="#page-'. $pane_id .'">'. $content->content .'</div>' : $content->content;
    $output .= $content->content;
  }

  return $output;
}

/**
 * Settings form callback.
 */
function ctools_demos_style_settings_form($settings) {
  $form = array();
  
  ctools_include('dependent');
  
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#default_value' => $settings['type'],
    '#options' => array(
      'none' => t('Nothing at all'),
      'manual' => t('Manual templating'),
    ),
  );
  
  $form['template'] = array(
    '#type' => 'textarea',
    '#title' => t('Template'),
    '#default_value' => $settings['template'],
    '#description' => '@todo implement contexts substitution/token',
    '#process' => array(
      'ctools_dependent_process'
    ),
    '#dependency' => array(
      'edit-settings-type' => array(
        'manual'
      ),
    )
  );
  
  return $form;
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_ctools_demos_style_render_pane($content, $pane, $display) {
  return $content->content;
}