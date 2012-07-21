// $Id: galleryformatter.js,v 1.1.2.3 2010/05/31 09:00:50 manuelgarcia Exp $

Drupal.behaviors.galleryformatter = function (context) {
  $('.galleryformatter:not(.gallery-processed)', context).each(function(){
    Drupal.galleryformatter.prepare(this);

  }).addClass('gallery-processed');
};

Drupal.galleryformatter = Drupal.galleryformatter || {};

// setting up the main behaviour
Drupal.galleryformatter.prepare = function(el) {
  // var $settings = Drupal.settings.galleryformatter;
  $el = $(el);
  var $slides = $('li.gallery-slide', $el);
  var $slideContainer = $('div.gallery-slides', $el);

  var $thumbs = $('.gallery-thumbs', $el);
  var $thumbsLi = $('li', $thumbs);
  var thumbWidth = $thumbsLi.filter(':first').width() + 'px';

  /*
   * @fixme
   * Only start the thumbs carrousel if needed ?
   * This can get very messy with padding etc
   * Reluctant to implement for now, though the if commented here seems to work fine
   */
  // if (($thumbsLi.size() * parseInt(thumbWidth)) >= $slideContainer.width()) {
  $('ul', $thumbs).width('9999px');
  $thumbs.infiniteCarousel();
  //}

  $thumbsLi = $('li', $thumbs); // we need to reselect because infiniteCarousel inserts new empty li elements if necessary

  $thumbsLi.each(function(){
    $(this).css({
        width: thumbWidth
      });
  });
  var $thumbslinks = $('a', $thumbsLi);

  // hide all slides, then show the first one
  $slides.hide();
  $slides.filter(':first').show();
  $thumbsLi.filter('.slide-0:not("cloned")').addClass('active');

  /*
   * @TODO:
   * figure out how to get this into proper functions reusing selections
   */
  $thumbslinks.click(function(e){
    $hash = $(this.hash);
    if(!$hash.is(':visible')){
      $thumbsLi.removeClass('active');
      $(this).parent().addClass('active');
      $slides.filter(':visible').fadeOut('slow');
      $hash.fadeIn('slow');
      /*
       * @FIXME
       * Need to figure out a way to update the location bar of the browser, for bookmarking etc, without making the scroll jump
       * window.location.hash = this.hash; solution below does update the location, but makes the scroll jump.
       */
      // window.location.hash = this.hash;  // not sure if this is the best way to do it.
    }
    e.preventDefault();
  });

  var $locationHash = window.location.hash;
  if ($locationHash) {
   $thumbslinks.filter("[href="+$locationHash+"]").click();  // trigger click event if going directly to the url of one of the tabs
  }
}
