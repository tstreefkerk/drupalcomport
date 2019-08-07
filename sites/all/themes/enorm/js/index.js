(function ($) {
    Drupal.behaviors.enorm = {
        attach: function (context, settings) {
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
