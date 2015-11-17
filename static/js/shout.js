var shoutApp = angular.module('shoutApp', []);

shoutApp.controller('ShoutController', function($scope, $http) {
  var shout = this;
  shout.users = [ ];

  $http.get('/users').success(function(data) {
    shout.users = data;
  });
});

shoutApp.controller('RegisterController', ['$scope', '$http', '$window', function($scope, $http, $window) {
  $scope.register = function(){
    $http.post('/register', '{ "name": "foobarbazz" }').then(function(){
      $window.location.reload(); },
      function(data){
        if(!data.data.success && data.data.code === 1) {
          $window.alert("User already exists");
        }
      });
  };
}]);
