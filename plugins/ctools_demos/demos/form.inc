<?php
$plugin = array(
  'title' => t('Form utilities'),
  'description' => t('drupal_get_form() should be a thing of the past...'),
  'hook menu' => 'ctools_demos_form_menu',
);



function ctools_demos_form_ctools_demos_demos_render($plugin) {
  ctools_include('form');
  $output = '';

  $form_id = 'ctools_demos_form_exmaple';
  $form_state = array(
    'want form' => TRUE, // will only return the FAPI array! Damn.. that's neat!
  );
  $form = ctools_build_form($form_id, $form_state);
  
  
  $output .= ctools_demos_highlight("
\$form_id = 'ctools_demos_form_exmaple';
\$form_state = array(
  'want form' => TRUE, // will only return the FAPI array! Damn.. that's neat!
);
\$form = ctools_build_form(\$form_id, \$form_state);");
  
  $code_fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('The returned FAPI array'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,
    'code' => array('#value' => ctools_demos_highlight(var_export($form, TRUE))),
  );
  $output .= drupal_render($code_fieldset);
  
  
  $output .= drupal_render($form);
  
  
  return $output;
}

function ctools_demos_form_menu($plugin) {
  $hooks = array();
  $hooks['ctools-demos/form/%ctools_js/do'] = array(
    'title' => 'A callback for the form demo',
    'page callback' => 'ctools_demos_form_ajax_callback',
    'page arguments' => array(2),
    'access arguments' => array('access content'),
  );
  return $hooks;
}


function ctools_demos_form_ajax_callback($js = FALSE) {
  ctools_include('ajax');
  ctools_include('form');
  
  $form_id = 'ctools_demos_form_exmaple';
  $form_state = array(
    'no_redirect' => TRUE,
    'want form' => TRUE,
  );
  
  
  $form = ctools_build_form($form_id, $form_state);
  
  
  if ($js) {
    $commands = array();
    $commands = ctools_ajax_command_replace($selector, drupal_render($form[$form_element]));
    ctools_ajax_render($commands);
  }
  else {
    return drupal_render($form);
  }
}

function ctools_demos_form_exmaple(&$form_state, $arg1 = NULL) {
  
  $form['selection'] = array(
    '#type'     => 'select',
    '#title'    => t('Selection'),
    '#options'  => array(
      ''          => t('None'),
      'group1'    => t('Group @group', array('@group' => 1)),
      'group2'    => t('Group @group', array('@group' => 2)),
      'group3'    => t('Group @group', array('@group' => 3)),
    ),
  );
  
  
  $form['group1'] = array(
    '#type'     => 'fieldset',
    '#title'    => t('Group @group', array('@group' => 1)),
    '#tree'     => TRUE,
    'option1'   => array(
      '#type'     => 'select',
      '#title'    => t('Group option'),
      '#options'  => array(
        'option1'   => 1,
        'option2'   => 2,
        'option3'   => 3,
      ),
    ),
  );
  
  $form['group2'] = array(
    '#type'     => 'fieldset',
    '#title'    => t('Group @group', array('@group' => 2)),
    '#tree'     => TRUE,
    'option1'   => array(
      '#type'     => 'select',
      '#title'    => t('Group option'),
      '#options'  => array(
        'option1'   => 1,
        'option2'   => 2,
        'option3'   => 3,
      ),
    ),
  );
  
  $form['group3'] = array(
    '#type'     => 'fieldset',
    '#title'    => t('Group @group', array('@group' => 3)),
    '#tree'     => TRUE,
    'option1'   => array(
      '#type'     => 'select',
      '#title'    => t('Group option'),
      '#options'  => array(
        'option1'   => 1,
        'option2'   => 2,
        'option3'   => 3,
      ),
    ),
  );
  
  return $form;
}