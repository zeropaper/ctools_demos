<?php

$plugin = array(
  'page callback'   => 'ctools_demos_dependent_page',
  'description'     => t('Allows to show/hide form elements depending on a user choice.'),
);

function ctools_demos_dependent_page() {
  return drupal_get_form('ctools_demos_dependent_form');
}

function ctools_demos_dependent_form(&$form_state) {
  ctools_include('dependent');
  
  $form = array();
  
  $form['menu'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Menu settings'),
    '#tree'         => TRUE,
  );
  
  $form['menu']['type'] = array(
    '#title'          => t('Menu type'),
    '#type'           => 'radios',
    '#options'        => array(
      'none'        => t('No menu entry'),
      'normal'      => t('Normal menu entry'),
      'tab'         => t('Menu tab'),
      'default tab' => t('Default menu tab'),
    ),
    '#default_value'  => 'none',
  );
  
  $form['menu']['title'] = array(
    '#title'          => t('Title'),
    '#type'           => 'textfield',
    '#default_value'  => '',
    '#description'    => t('If set to normal or tab, enter the text to use for the menu item.'),
    '#process'        => array(
      'ctools_dependent_process'
    ),
    '#dependency'     => array(
      'radio:menu[type]' => array(
        'normal',
        'tab',
        'default tab'
      )
    ),
  );
  
  
  
  $form['test2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select test2 type'),
    '#tree' => TRUE,
  );
  
  $form['test2']['type'] = array(
    '#title' => t('Object type'),
    '#type' => 'textfield',
  );
  
  $form['test2']['field'] = array(
    '#type' => 'textfield',
    '#title' => t('Just a field'),
    '#description'    => t('If set to normal or tab, enter the text to use for the menu item.'),
    
    '#process'        => array(
      'ctools_dependent_process'
    ),
    '#dependency'     => array(
      'edit-test2-type' => array(
        'node',
      )
    ),
  );
    

  $form['test2']['field']['#description'] = ctools_demos_highlight(var_export($form['test2'], TRUE));
  
  
  
  
  
  
  
  return system_settings_form($form);
}
