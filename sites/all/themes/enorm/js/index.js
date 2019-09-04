(function ($) {
    Drupal.behaviors.enorm = {
        attach: function (context, settings) {
            var $percentage = $(".field-name-field-project-percentage").find('.field-item').text();
            $(".milestone-percentage-bar").css("width", $percentage);
            $(".milestone-percentage-bar").text($percentage);
            $(".company-search-form-company-id").once('enorm').click(function() {
                var copyText = $(".company-search-form-company-id");
                copyText.select();
                document.execCommand("copy");
            });
            $(".view-header").once('enorm').click(function () {
                if ($(this).next(".view-content").hasClass("vanishIn")) {
                    $(this).next(".view-content").removeClass("vanishIn").addClass("vanishOut");
                }
                else {
                    $(this).next(".view-content").removeClass("hidden vanishOut").addClass("vanishIn");
                }
            });
            if($("body").hasClass("front"))
            {
            $(".col-sm-12").addClass("magictime spaceInDown").removeClass("hidden");
            }

        }
    };
}(jQuery));
