
(function($) {

  Drupal.behaviors.page_throbber = {
    attach: function (context) {
      var close = Drupal.settings.page_throbber.close;
      var settings = Drupal.settings.page_throbber.pages;
      if (settings !== null) {
        if (close) {
          $('body').once().append('<div id="throbber-message"><div id="throbber-close"></div><p></p></div>');
        }
        else {
          $('body').once().append('<div id="throbber-message"><p></p></div>');
        }        
      }
      var tmp = '';
      // treat all links looking for throbber parameter
      $('a').each(function() {
        tmp = getURLParameter('throbber', $(this).attr('href'));
        if (tmp) {
          $(this).addClass('throbber-link');
          $(this).data('key', tmp);
          // remove throbber parameter from url
          href = $(this).attr('href');
          href = href.replace('?throbber=1','');
          $(this).attr('href', href);
        }
      });

      // Click event on links
      $("a.throbber-link").live("click", function(e){ 
        var key = $(this).data('key');
        var msg = settings["page_throbber_page_row_"+key]["page_throbber_page_message_"+key]; 
        loadThrobber(msg);
        // Safari, introduce 0.2 second delay, otherwise it doesn't trigger
        e.preventDefault();
        var goTo = this.getAttribute("href");
        setTimeout(function(){
             window.location = goTo;
        },200);
      });

      var formbuttons = Drupal.settings.page_throbber.buttons;

      // trigger form button clicks
      if (formbuttons) {
        $.each(formbuttons, function(key, value) {
          $(value.id).click(function(e){ 
            e.preventDefault();
            // delay form 0.2 seconds so Safari can draw on DOM
            form = $(this).parents('form');
            setTimeout(function(){
              form.submit();
            },200);
            var key = value.key.replace('page_throbber_page_buttons_', '');
            var msg = settings["page_throbber_page_row_"+key]["page_throbber_page_message_"+key];
            loadThrobber(msg);
          });
        });
      }

      // add click event to close button
      $('#throbber-message #throbber-close').live('click', function(){  
        $("#lean_overlay").fadeOut(300);
        $('#throbber-message').css({ 'display' : 'none' });
      }); 

      // hack to fix issue with firefox/pc and safari when using back button
      $(window).unload(function(){});
      // fix IE11 issue with bfcache
      $(window).focus(function() {
        $("#lean_overlay").remove();
        $('#throbber-message').css({ 'display' : 'none' });
      });

    }       
  }

  function loadThrobber(msg) {
    $('#throbber-message p').html(msg);
    $('body').leanModalThrobber();
  }

  $.fn.extend({ 
      leanModalThrobber: function() {
          var overlay = $('<div id="lean_overlay"></div>');
          var modal_id = "#throbber-message";

          if ($(modal_id).length > 0) {
            $('body').append(overlay);
            var modal_height = $(modal_id).outerHeight();
            var modal_width = $(modal_id).outerWidth();

            $("#lean_overlay").css({ 'display' : 'block', opacity : '0.5'});

            $(modal_id).css({ 
              'display' : 'block',
              'position' : 'fixed',
              'left' : '50%',
              'margin-left' : -(modal_width/2) + "px",
              'top' : "150px"
            });

            $(modal_id).spin("small").css('opacity', '1');

          }
      }
  });

  /*
  $("#el").spin(); // Produces default Spinner using the text color of #el.
  $("#el").spin("small"); // Produces a 'small' Spinner using the text color of #el.
  $("#el").spin("large", "white"); // Produces a 'large' Spinner in white (or any valid CSS color).
  $("#el").spin({ ... }); // Produces a Spinner using your custom settings.

  $("#el").spin(false); // Kills the spinner.
  */
  $.fn.spin = function(opts, color) {
    var presets = {
      "tiny": { lines: 8, length: 2, width: 2, radius: 3 },
      "small": { lines: 8, length: 4, width: 3, radius: 5 },
      "large": { lines: 10, length: 8, width: 4, radius: 8 }
    };
    if (Spinner) {
      return this.each(function() {
        var $this = $(this),
          data = $this.data();
        
        if (data.spinner) {
          data.spinner.stop();
          delete data.spinner;
        }
        if (opts !== false) {
          if (typeof opts === "string") {
            if (opts in presets) {
              opts = presets[opts];
            } else {
              opts = {};
            }
            if (color) {
              opts.color = color;
            }
          }
          data.spinner = new Spinner($.extend({color: $this.css('color')}, opts)).spin(this);
        }
      });
    } else {
      throw "Spinner class not available.";
    }
  };

    }

)(jQuery);

function getURLParameter(name, url) {
  return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(url)||[,""])[1].replace(/\+/g, '%20'))||null;
}