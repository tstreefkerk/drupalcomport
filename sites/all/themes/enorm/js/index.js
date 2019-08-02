$(document).ready(function() {
    console.log("hello");
    $(".view-header").addClass("hidden");
    $(".view-header").click(function () {
        $(".view-content").slideDown().removeClass("hidden");
    })
});