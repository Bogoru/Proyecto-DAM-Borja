'use strict';

Object.defineProperty(exports, '__esModule', { value: true });

var tslib = require('tslib');
var core$1 = require('@angular/core');
var core = require('@ionic-native/core');
require('rxjs');

var BLE = /** @class */ (function (_super) {
    tslib.__extends(BLE, _super);
    function BLE() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    BLE.prototype.scan = function (services, seconds) { return core.cordova(this, "scan", { "observable": true }, arguments); };
    BLE.prototype.startScan = function (services) { return core.cordova(this, "startScan", { "observable": true, "clearFunction": "stopScan", "clearWithArgs": false }, arguments); };
    BLE.prototype.startScanWithOptions = function (services, options) { return core.cordova(this, "startScanWithOptions", { "observable": true, "clearFunction": "stopScan", "clearWithArgs": false }, arguments); };
    BLE.prototype.stopScan = function () { return core.cordova(this, "stopScan", {}, arguments); };
    BLE.prototype.setPin = function (pin) { return core.cordova(this, "setPin", { "observable": true }, arguments); };
    BLE.prototype.connect = function (deviceId) { return core.cordova(this, "connect", { "observable": true, "clearFunction": "disconnect", "clearWithArgs": true }, arguments); };
    BLE.prototype.autoConnect = function (deviceId, connectCallback, disconnectCallback) { return core.cordova(this, "autoConnect", { "sync": true }, arguments); };
    BLE.prototype.requestMtu = function (deviceId, mtuSize) { return core.cordova(this, "requestMtu", {}, arguments); };
    BLE.prototype.refreshDeviceCache = function (deviceId, timeoutMillis) { return core.cordova(this, "refreshDeviceCache", {}, arguments); };
    BLE.prototype.disconnect = function (deviceId) { return core.cordova(this, "disconnect", {}, arguments); };
    BLE.prototype.read = function (deviceId, serviceUUID, characteristicUUID) { return core.cordova(this, "read", {}, arguments); };
    BLE.prototype.write = function (deviceId, serviceUUID, characteristicUUID, value) { return core.cordova(this, "write", {}, arguments); };
    BLE.prototype.writeWithoutResponse = function (deviceId, serviceUUID, characteristicUUID, value) { return core.cordova(this, "writeWithoutResponse", {}, arguments); };
    BLE.prototype.startNotification = function (deviceId, serviceUUID, characteristicUUID) { return core.cordova(this, "startNotification", { "observable": true, "destruct": true, "clearFunction": "stopNotification", "clearWithArgs": true }, arguments); };
    BLE.prototype.stopNotification = function (deviceId, serviceUUID, characteristicUUID) { return core.cordova(this, "stopNotification", {}, arguments); };
    BLE.prototype.isConnected = function (deviceId) { return core.cordova(this, "isConnected", {}, arguments); };
    BLE.prototype.isEnabled = function () { return core.cordova(this, "isEnabled", {}, arguments); };
    BLE.prototype.startStateNotifications = function () { return core.cordova(this, "startStateNotifications", { "observable": true, "clearFunction": "stopStateNotifications", "clearWithArgs": false }, arguments); };
    BLE.prototype.stopStateNotifications = function () { return core.cordova(this, "stopStateNotifications", {}, arguments); };
    BLE.prototype.showBluetoothSettings = function () { return core.cordova(this, "showBluetoothSettings", {}, arguments); };
    BLE.prototype.enable = function () { return core.cordova(this, "enable", {}, arguments); };
    BLE.prototype.readRSSI = function (deviceId) { return core.cordova(this, "readRSSI", {}, arguments); };
    BLE.prototype.connectedPeripheralsWithServices = function (services) { return core.cordova(this, "connectedPeripheralsWithServices", {}, arguments); };
    BLE.prototype.peripheralsWithIdentifiers = function (uuids) { return core.cordova(this, "peripheralsWithIdentifiers", {}, arguments); };
    BLE.prototype.bondedDevices = function () { return core.cordova(this, "bondedDevices", {}, arguments); };
    BLE.prototype.isLocationEnabled = function () { return core.cordova(this, "isLocationEnabled", {}, arguments); };
    BLE.pluginName = "BLE";
    BLE.plugin = "cordova-plugin-ble-central";
    BLE.pluginRef = "ble";
    BLE.repo = "https://github.com/don/cordova-plugin-ble-central";
    BLE.platforms = ["Android", "iOS"];
    BLE.decorators = [
        { type: core$1.Injectable }
    ];
    return BLE;
}(core.IonicNativePlugin));

exports.BLE = BLE;
