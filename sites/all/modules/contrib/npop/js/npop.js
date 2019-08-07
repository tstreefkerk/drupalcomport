(function ($) {
  'use strict';
  /**
   * Create url change by History API ajax command.
   *
   * @param {object} ajax Global Drupal.ajax object.
   * @param {object} response Response data.
   * @param {string} status Status of command.
   */
  Drupal.ajax.prototype.commands.npop_change_url = function (ajax, response, status) {
    var isHistoty = !!(window.history && history.pushState);
    if (isHistoty) {
      if (response.hasOwnProperty('toparent')) {
        history.pushState(null, null, $(response.toparent).data('parnet'));
      } else {
        history.pushState(null, null, response.url);
      }
    }
  };

  /**
   * Add feature - close popup by overlay click.
   *
   * @param {object} current context.
   * @param {object} ajax Global Drupal.settings object.
   */
  Drupal.behaviors.npopOverlay = {
    attach: function (context, settings) {
      if(settings.npop_overlay_close){
        var $npop = $('.npop').once('npop');
        $npop.on('click', '.node', function(event){
          event.stopPropagation();
        });
        $npop.click(function () {
          $('.npop-close-btn').click();
        });
      }
    }
  };
}(jQuery));
