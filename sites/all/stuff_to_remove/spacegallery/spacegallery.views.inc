<?php  // $Id: spacegallery.views.inc,v 1.1 2010/03/12 21:04:37 rashad612 Exp $

/**
 * Implementation of hook_views_plugins().
 *
 */
function spacegallery_views_plugins() {
  
  return array(
    'module' => 'spacegallery',
    'style'  => array(
      'spacegallery' => array(
        'title' => t('Space Gallery'),
        'theme' => 'spacegallery_view',
        'help' => 'Display images as Space Gallery',
        'handler' => 'spacegallery_style_plugin',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal'
      )
    )
  );
}// end function spacegallery_views_plugins;
