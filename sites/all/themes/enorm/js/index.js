(function ($) {
    Drupal.behaviors.enorm = {
        attach: function (context, settings) {
            var $percentage = $(".percentage-done-hidden").text();
            $(".milestone-percentage-bar").css("width", $percentage);
            $(".milestone-percentage-bar").text($percentage);
            $(".field-name-field-company-telephone").after("<div id='line-break'></div>");
            $(".field-name-field-project-end-date").after("<div id='line-break'></div>");
            $(".field-name-field-project-participants").after("<div id='line-break'></div>");
            $(".field-name-field-project-description").after("<div id='line-break'></div>");
            $(".field-name-field-callback-request-done").after("<div id='line-break'></div>");
            $(".project-expiring").prependTo("#node-content-type-project-detail");
            $(".page-all-projects-customer .views-field-title a").click(function (e) {
                $(".col-sm-12").fadeOut();
                $(".row").addClass('enorm-spinner-container').html("<img src='/sites/all/themes/enorm/assets/img/enorm-loader-transparent.gif' class='enorm-spinner'><br><p>Loading...</p>");
            });
            $(".page-all-companies-nodes .views-field-title a").click(function (e) {
                $(".col-sm-12").fadeOut();
                $(".row").addClass('enorm-spinner-container').html("<img src='/sites/all/themes/enorm/assets/img/enorm-loader-transparent.gif' class='enorm-spinner'><br><p>Loading...</p>");
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
