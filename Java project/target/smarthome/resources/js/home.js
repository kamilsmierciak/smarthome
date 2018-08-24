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
        }).done(function (data) {
            ledstat = JSON.parse(data);
            if (ledstat.status.equals("off")) {
                $.ajax({
                    method: "GET",
                    url: "http://192.168.88.47/led?turn=on",
                }).done(function () {
                    console.log('hura');
                }).fail(function (xhr, status, errorThrown) {
                    console.log("BŁĄD!", xhr, status, errorThrown);
                });
            } else {
                $.ajax({
                    method: "GET",
                    url: "http://192.168.88.47/led?turn=off"
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
            url: "http://espkamil.local/json"
        }).done(function(plug){
            var json = JSON.parse(plug);
            plugstatString = json.plug;
        })
    };
    plugStat();

    stat.innerHTML = plugstatString;

    colorpicker.css("display", "none");

    lights.click(function(){
        colorpicker.slideDown()
    })

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
        var json = '"red":' + red +', "green":'+green+', "blue":'+ blue+'}';
        $.ajax({
            url: "http://espkamil.local/rgb",
            type: "POST",
            data: JSON.stringify(json),
            contentType: "application/json"
        }).done(
            console.log("wysłano jsona")
        ).fail(
            console.log("Nic nie działa!! Dzwoń po JSONA")
        )

    })
    drive.click(function(){
        window.location.replace("ftp://10.156.86.197:2221");
    })

});