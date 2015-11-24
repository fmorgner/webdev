var shoutApp = angular.module('shoutApp', ['ui.bootstrap', 'ngCookies']);

shoutApp.controller('RegisterController', ['$scope', '$http', '$window', function($scope, $http, $window) {

  $scope.register = function(ev){
    var success = function(data){ $window.location.reload(); };
    var failure = function(data){ if(!data.data.success && data.data.code === 1) { $window.alert("User already exists"); }};
    $http.post('/register', '{ "name": "' + ev.target.attributes['data-name'].value + '" }').then(success, failure);
  };

}]);

shoutApp.controller('ShoutController',  ['$scope', '$http', '$window', '$cookies', function($scope, $http, $window, $cookies) {

  $scope.shouts = [];
  $scope.notifications = [];

  var id = $cookies.get("session");

  var success = function(data) { $scope.shouts = data.data };

  $http.get('/shouts/' + id).then(success, $window.alert);

  $scope.closeNotification = function(index) {
    $scope.notifications.splice(index, 1);
  };

  $scope.shout = function(ev) {
    ev.target.disabled = true;

    var success = function(data) {
      ev.target.disabled = false;
      $scope.shoutText = '';
      $scope.shouts.splice(0, 0, data.data);
      $scope.notifications.splice(0, 0, { text : "Success!", style : "success" });
    };

    var failure = function(data) {
      $scope.notifications.splice(0, 0, { text : "An error occured!", style : "danger" });
    };

    var newShout = {};
    newShout["text"] = $scope.shoutText;
    $http.post('/shout', JSON.stringify(newShout)).then(success, failure);
  };

}]);

