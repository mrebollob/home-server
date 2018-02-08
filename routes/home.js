var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {

    var status ={
        status: "OPEN"
    }

  res.json(status);
});

module.exports = router;
