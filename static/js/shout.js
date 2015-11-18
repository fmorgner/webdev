var shoutApp = angular.module('shoutApp', ['ui.bootstrap']);

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
    $http.post('/register', '{ "name": "' + ev.target.attributes['data-name'].value + '" }').then(success, failure)
  };

}]);

shoutApp.controller('ShoutController',  ['$scope', '$http', '$window', function($scope, $http, $window) {

  $scope.shout = function(ev) {
    ev.target.disabled = true;
    $scope.shoutForm.$setPristine();

    var success = function(data) { $scope.shoutForm.$setPristine() };
  };

}]);
