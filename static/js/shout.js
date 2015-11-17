angular.module('shoutApp', [])
.controller('ShoutController', function($scope, $http) {
  var shout = this;

  shout.users = [ ];

  $http.get('/users').success(function(data) {
    shout.users = data;
  });

  //console.log({where:'MeineGalerieController.constructor', self: this, $scope: $scope, $http: $http});
});

