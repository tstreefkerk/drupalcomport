(function ($) {
  'use strict';

  /**
   * Processing links with data attribute npop.
   */
  Drupal.behaviors.npopAjax = {
    attach: function (context, settings) {
      $('a[data-npop]:not(.npop-ajax-processed)', context).each(function (e) {
        var $link = $(this);
        $link.addClass('npop-ajax-processed');
        if ($link.hasClass('use-ajax')) {
          $link.removeClass('use-ajax').removeClass('ajax-processed');
          $link.unbind('click');
        }
        var nid = parseInt($link.data('npop'));

        // Append get parameters query if exists.
        var href = $link.attr('href');
        if (href.search(/\?/) !== -1) {
                var query = '?' + href.split('?').pop();
        } else {
                var query = '';
        }
        var element_settings = {};
        element_settings.url = '/ajax/npop/node/' + nid + '/load/nojs' + query;
        element_settings.setClick = true;
        element_settings.event = 'click';
        element_settings.progress = {type: 'throbber'};
        var base = 'npop-' + nid;
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);

      });
    }
  };
}(jQuery));
