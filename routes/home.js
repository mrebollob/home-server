var express = require('express');
var router = express.Router();
var request = require('request');
var devices = require('../config').devices;


/**
 * Return a list of devices with its configuration
 */
router.get('/devices', function (req, res, next) {
    res.json(devices)
});

/**
 * Open specific device
 */
router.get('/open/:key', function(req, res, next) {
    // Get the device by the provided key
    var config = devices[req.params.key];

    // Device not found
    if (!config) return res.json({ status: 'ERROR', message: 'Key not found' });

    request.get(`http://${config.ip}:${config.port}/open`, function (_err, _res, _body) {
        // Error response
        if (_err) return res.json({ status: 'ERROR' });

        // Successful response
        return res.json(JSON.parse(_body));
    })
});

module.exports = router;
