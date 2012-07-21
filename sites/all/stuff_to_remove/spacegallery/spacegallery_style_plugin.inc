<?php  // $Id: spacegallery_style_plugin.inc,v 1.1 2010/03/12 21:04:37 rashad612 Exp $

/**
 * Implementation of views_plugin_style().
 *
 */
class spacegallery_style_plugin extends views_plugin_style {
  
  function option_definition() {
    $options = parent::option_definition();
    
    /**
    Options
    A hash of parameters. All parameters are optional.
    
    border: 	      (integer)   Images' border. Default: 0
    duration: 	    (integer)   Animation duration. Default 800
    perspective: 	(integer) 	  Perpective height. Default: 140
    minScale:     	(float) 	    Minimum scale for the image in the back. Default: 0.2
    loadingClass: 	(string) 	  CSS class applied to the element while looading images. Default: null
    **/
    
    $options['border'] = array('default' => 0);
    $options['duration'] = array('default' => 800);
    $options['perspective'] = array('default' => 140);
    $options['minScale'] = array('default' => 0.2);
    $options['loadingClass'] = array('default' => 'loading');
   
    return $options;
  }// end function option_definition;
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['border'] = array(
      '#type' => 'textfield',
      '#title' => t('Border'),
      '#default_value' => $this->options['border'],
      '#size' => 5,
      '#description' => t('(integer) Images\' border.'), 
      '#required' => TRUE
    );
    
    $form['duration'] = array(
      '#type' => 'textfield',
      '#title' => t('Duration'),
      '#default_value' => $this->options['duration'],
      '#size' => 5,
      '#description' => t('(integer) Animation duration.'), 
      '#required' => TRUE
    );
    
    $form['perspective'] = array(
      '#type' => 'textfield',
      '#title' => t('Perspective'),
      '#default_value' => $this->options['perspective'],
      '#size' => 5,
      '#description' => t('(integer) Perpective height.'), 
      '#required' => TRUE
    );
    
    $form['minScale'] = array(
      '#type' => 'textfield',
      '#title' => t('Minimum Scale'),
      '#default_value' => $this->options['minScale'],
      '#size' => 5,
      '#description' => t('(float) Minimum scale for the image in the back.'), 
      '#required' => TRUE
    );
    
    $form['loadingClass'] = array(
      '#type' => 'textfield',
      '#title' => t('Loading CSS Class'),
      '#default_value' => $this->options['loadingClass'],
      '#size' => 20,
      '#description' => t('CSS class applied to the element while looading images.'), 
      '#required' => TRUE
    );
    
  }// end function options_form;

}// end class spacegallery_style_plugin;
