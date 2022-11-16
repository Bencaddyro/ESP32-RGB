
var hidden = true;

function updatePatternPanel(){

    document.getElementById("pattern_full").style.display = 'none';
    document.getElementById("pattern_blink").style.display = 'none';
    document.getElementById("pattern_light").style.display = 'none';
    document.getElementById("pattern_wipe").style.display = 'none';
    document.getElementById("pattern_police").style.display = 'none';
    document.getElementById("pattern_snake").style.display = 'none';
    document.getElementById("pattern_firework").style.display = 'none';

    pattern = parseInt(document.getElementById("patternSelector").value);
    switch (pattern) {
    // Full
    case 0:
        document.getElementById("pattern_full").style.display = 'block';
        break;
    // Blink
    case 1:
        document.getElementById("pattern_blink").style.display = 'block';
        break;
    // Light
    case 2:
        document.getElementById("pattern_light").style.display = 'block';
        break;
    // Wipe
    case 4:
        document.getElementById("pattern_wipe").style.display = 'block';
        break;
    // Police
    case 5:
        document.getElementById("pattern_police").style.display = 'block';
        break;
    // Snake
    case 6:
        document.getElementById("pattern_snake").style.display = 'block';
        break;
    // Firework
    case 7:
        document.getElementById("pattern_firework").style.display = 'block';
        break;
    default:
        console.log("Invalid hidden pattern");
    };

}

function secretParam() {
    console.log("SecretClick");
    if(hidden){
        document.getElementById("secretParameters").style.display = 'block';

    } else {
        document.getElementById("secretParameters").style.display = 'none';
    }
    hidden = !hidden;
}

function getParameters() {
    $.post("getParameters",
          { pattern: document.getElementById("patternSelector").value },
           function(data) {
               console.log(data);
               document.getElementById("currentParameters").innerHTML = data;
           });

}

function setParameters(pattern) {
    switch (pattern) {
    // Full
    case 0:
        activeColor = color_full.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        rainbow = 0;
        if(document.getElementById("full_rainbow").checked) {
            color = color_full.color.value;
            rainbow = 1;
        }
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("full_speed").value,
            1: color,
            2: rainbow,
        });
        break;
    // Blink
    case 1:
        activeColor = color_blink.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        rainbow = 0;
        if(document.getElementById("blink_rainbow").checked) {
            color = color_blink.color.value;
            rainbow = 1;
        }
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("blink_speed").value,
            1: color,
            2: document.getElementById("blink_gap").value,
            3: rainbow,
        });
        break;
    // Light
    case 2:
        activeColor = color_light.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        $.post("setParameters", {
            pattern: pattern,
            0: 50,
            1: color,
            2: color_light.color.value,
        });
        break;
    // Wipe
    case 4:
        activeColor = color_wipe.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        rainbow = 0;
        if(document.getElementById("wipe_rainbow").checked) {
            color = color_wipe.color.value;
            rainbow = 1;
        }
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("wipe_speed").value,
            1: color,
            2: rainbow,
        });
        break;
    // Police
    case 5:
        activeColor1 = color_police.colors[0].hexString;
        activeColor2 = color_police.colors[1].hexString;
        color1 = parseInt(activeColor1.substring(1), 16);
        color2 = parseInt(activeColor2.substring(1), 16);
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("police_speed").value,
            1: color1,
            2: color2,
        });
        break;
    // Snake
    case 6:
        activeColor = color_snake.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        rainbow = 0;
        if(document.getElementById("snake_rainbow").checked) {
            color = color_snake.color.value;
            rainbow = 1;
        }
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("snake_speed").value,
            1: color,
            2: document.getElementById("snake_number").value,
            3: document.getElementById("snake_lenght").value,
            4: rainbow,
        });
        break;
    // Firework
    case 7:
        activeColor = color_firework.color.hexString;
        color = parseInt(activeColor.substring(1), 16);
        rainbow = 0;
        if(document.getElementById("firework_rainbow").checked) {
            color = color_firework.color.value;
            rainbow = 1;
        }
        $.post("setParameters", {
            pattern: pattern,
            0: document.getElementById("firework_speed").value,
            1: color,
            2: document.getElementById("firework_number").value,
            3: document.getElementById("firework_radius").value,
            4: rainbow,
        });
        break;
    default:
        console.log("Invalid Pattern");
    }
}

function setNumber() {
    $.post("setNumber", {
        number: document.getElementById("ledNumber").value
    });
}


function setPattern(item) {
    updatePatternPanel();
    console.log("Pattern :" + item.value);
    $.post("setPattern", {
        pattern: item.value
    });
}

function onButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "on", true);
    xhttp.send();
}

function offButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "off", true);
    xhttp.send();
}



var color_full = new iro.ColorPicker('#picker_full', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_full.on('input:change', function() {
    setParameters(0);
  }
);

var color_blink = new iro.ColorPicker('#picker_blink', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_blink.on('input:change', function() {
    setParameters(1);
  }
);

var color_light = new iro.ColorPicker('#picker_light', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'kelvin'
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_light.on('input:change', function() {
    setParameters(2);
  }
);

var color_wipe = new iro.ColorPicker('#picker_wipe', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_wipe.on('input:change', function() {
    setParameters(4);
  }
);

var color_police = new iro.ColorPicker('#picker_police', {
    colors: [
    'rgb(100%, 0, 0)',
    'rgb(0, 0, 100%)',
    ],
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            handleRadius: 15,
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value',
        activeIndex: 0,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value',
        activeIndex: 1,
        }},
    ]
});

color_police.on('input:change', function() {
    setParameters(5);
  }
);

var color_snake = new iro.ColorPicker('#picker_snake', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_snake.on('input:change', function() {
    setParameters(6);
  }
);

var color_firework = new iro.ColorPicker('#picker_firework', {
    borderWidth: 5,
    borderColor: "#0c807d",
    handleRadius: 15,
    layout: [
        {
        component: iro.ui.Wheel,
        options: {
            wheelLightness: false,
        }},
        {
        component: iro.ui.Slider,
        options: {
        sliderType: 'value'
        }},
    ]
});

color_firework.on('input:change', function() {
    setParameters(7);
  }
);
