var shoutApp = angular.module('shoutApp', ['ui.bootstrap', 'ngCookies']);

shoutApp.controller('UsersController', function($scope, $http) {
  var that = this;
  that.users = [ ];

  $http.get('/users').success(function(data) {
    that.users = data;
  });

});

shoutApp.controller('RegisterController', ['$scope', '$http', '$window', function($scope, $http, $window) {

  $scope.register = function(ev){
    var success = function(data){ $window.location.reload(); };
    var failure = function(data){ if(!data.data.success && data.data.code === 1) { $window.alert("User already exists"); }};
    $http.post('/register', '{ "name": "' + ev.target.attributes['data-name'].value + '" }').then(success, failure);
  };

}]);

shoutApp.controller('ShoutController',  ['$scope', '$http', '$window', '$cookies', function($scope, $http, $window, $cookies) {

  $scope.shouts = [];

  var id = $cookies.get("session");

  var success = function(data) { $scope.shouts = data.data };

  $http.get('/shouts/' + id).then(success, $window.alert);

  $scope.shout = function(ev) {
    ev.target.disabled = true;
    var success = function(data) {
      ev.target.disabled = false;
      $scope.shoutText = '';
      $scope.shouts.splice(0, 0, data.data);
      console.log($scope.shouts);
    };
    var failure = function(data) { $window.alert("FAIL"); };
    $http.post('/shout', '{ "text": "' + $scope.shoutText + '" }').then(success, failure);
  };

}]);

