
  cordova.define('cordova/plugin_list', function(require, exports, module) {
    module.exports = [
      {
          "id": "cordova-plugin-ble-central.ble",
          "file": "plugins/cordova-plugin-ble-central/www/ble.js",
          "pluginId": "cordova-plugin-ble-central",
        "clobbers": [
          "ble"
        ]
        }
    ];
    module.exports.metadata =
    // TOP OF METADATA
    {
      "cordova-plugin-ble-central": "1.6.3"
    };
    // BOTTOM OF METADATA
    });
    