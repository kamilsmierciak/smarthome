$(document).ready(function () {
    var count = 0;
    var lights = $("#lights");
    var fan = $("#fan");
    var drive = $("#drive");
    var btn = $(".btn");
    var stat = $("#stat");
    var colorpicker = $("#colorpicker");
    var colorPickerInput = $("#colorPickerInput");

    btn.mouseenter(function () {
        $(this).addClass("mov");
    });
    btn.mousedown(function () {
        $(this).addClass("cl");
    });
    btn.mouseup(function () {
        $(this).removeClass("cl")
    });
    btn.mouseleave(function () {
        $(this).removeClass("mov")
    });
    fan.click(function () {
        var ledstat = "";
        $.ajax({
            method: "GET",
            url: "http://espkamil.local/json",
            data: "JSON"
        }).done(function (status) {
            // ledstat = JSON.parse(data);
            if (status.plug === "off") {
                stat.html("ON");
                $.ajax({
                    method: "GET",
                    url: "http://espkamil.local/plug?turn=on",
                }).done(function () {
                    console.log('hura');
                }).fail(function (xhr, status, errorThrown) {
                    console.log("BŁĄD!", xhr, status, errorThrown);
                });
            } else {
                stat.html("OFF");
                $.ajax({
                    method: "GET",
                    url: "http://espkamil.local/plug?turn=off"
                }).done(function () {
                    console.log('hura');
                }).fail(function (xhr, status, errorThrown) {
                    console.log("BŁĄD!", xhr, status, errorThrown);
                });
            }
        });

    });
    var plugstatString = "";
    function plugStat(){
        $.ajax({
            method: "GET",
            url: "http://espkamil.local/json",
            data: "JSON"
        }).done(function(status){
            // var json = JSON.parse(plug);
            // plugstatString = status.plug;
            stat.html(status.plug);
        })
    }
    plugStat();



    colorpicker.css("display", "none");

    lights.click(function(){
        colorpicker.slideDown()
    });

    colorPickerInput.click(function () {
        var red ="";
        var green = "";
        var blue = "";
        var colors1 = colorPickerInput.css("background-color");
        function rgb(r, g, b){
            red = r;
            green = g;
            blue = b;
        }
        eval(colors1);
        $.ajax({
            method: "GET",
            url: "http://espkamil.local/rgb?r="+red+"&g="+green+"&b="+blue,
        }).done(function () {
            console.log('hura');
        }).fail(function (xhr, status, errorThrown) {
            console.log("BŁĄD!", xhr, status, errorThrown);
        });

    });
    drive.click(function(){
        window.location.replace("ftp://192.168.88.50:2221");
    })

});