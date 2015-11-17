var shoutApp = angular.module('shoutApp', ['ui.bootstrap']);

shoutApp.controller('UsersController', function($scope, $http) {
  var shout = this;
  shout.users = [ ];

  $http.get('/users').success(function(data) {
    shout.users = data;
  });
});

shoutApp.controller('RegisterController', ['$scope', '$http', '$window', function($scope, $http, $window) {
  var success = function(data){ $window.location.reload(); };
  var failure = function(data){ if(!data.data.success && data.data.code === 1) { $window.alert("User already exists"); }};

  $scope.register = function(ev){
    $http.post('/register', '{ "name": "' + ev.target.attributes['data-name'].value + '" }').then(success, failure)};
}]);
