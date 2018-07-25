<!-- FIXED BUTTON - DOC AND PROFILE -->
<?php
    if(isset($_SESSION['logged']))
    {
        echo '<div class="fixed-action-btn horizontal click-to-toggle">';
        echo '<a class="btn-floating btn-large red lighten-1"><i class="large material-icons">format_quote</i></a>';
        echo '<ul>';
        echo '<li><a class="btn-floating red lighten-1" href="http://combathalloween.netne.net/bugs/other/documentation.php"><i class="material-icons">insert_chart</i></a></li>';
        echo '<li><a class="btn-floating blue lighten-1 sidenav-trigger" href="#" data-target="mobile-demo"><i class="material-icons">person</i></a></li>';
        echo '</ul>';
        echo '</div>';
    }
?>
</main>

<!-- Footer -->
<footer class="page-footer">
    <div class="container">
    <div class="row center">
        <div class="col s12 m4">
            <h5 class="white-text">Admins:</h5>
            <p class="white-text">Adrian Michałek: devmichalek@gmail.com</p>
        </div>
        <div class="col s12 m4">
            <h5 class="white-text">Moderators:</h5>
            <p class="white-text">Sebastian Bialucha: sebastek321@gmail.com</p>
            <p class="white-text">Kamil Gawlik: kamilgawlik@icloud.com</p>
        </div>
        <div class="col s12 m4">
            <h5 class="white-text">About:</h5>
            <p class="grey-text text-lighten-4">Project of SFML & QT.</p>
        </div>
    </div>
  <div class="footer-copyright col s12 m4">
    <a class="modal-trigger waves-effect waves-light btn" href="#license">©2018 Terms of Use</a>
  </div>
  </div>
</footer>

  <!-- LICENSE -->
<div id="license" class="modal modal-fixed-footer">
  <div class="modal-content">
    <h4 class="modcon">MIT License</h4>
    <div><p><?php require_once('LICENSE.txt'); ?></p></div>
  </div>
  <div class="modal-footer">
    <a href="#!" class="modal-action modal-close waves-effect waves-green btn-flat japokki">Agree</a>
  </div>
</div>

<!-- PRELOADER -->
    <div class="preloader-background">
    <div class="preloader-wrapper big active">
      <div class="spinner-layer spinner-blue">
        <div class="circle-clipper left">
          <div class="circle"></div>
        </div><div class="gap-patch">
          <div class="circle"></div>
        </div><div class="circle-clipper right">
          <div class="circle"></div>
        </div>
      </div>

      <div class="spinner-layer spinner-red">
        <div class="circle-clipper left">
          <div class="circle"></div>
        </div><div class="gap-patch">
          <div class="circle"></div>
        </div><div class="circle-clipper right">
          <div class="circle"></div>
        </div>
      </div>

      <div class="spinner-layer spinner-yellow">
        <div class="circle-clipper left">
          <div class="circle"></div>
        </div><div class="gap-patch">
          <div class="circle"></div>
        </div><div class="circle-clipper right">
          <div class="circle"></div>
        </div>
      </div>

      <div class="spinner-layer spinner-green">
        <div class="circle-clipper left">
          <div class="circle"></div>
        </div><div class="gap-patch">
          <div class="circle"></div>
        </div><div class="circle-clipper right">
          <div class="circle"></div>
        </div>
      </div>
    </div>
    </div>

<!-- Compiled and minified JavaScript -->
<script type="text/javascript" src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/js/materialize.min.js"></script>
<script type="text/javascript" src="http://combathalloween.netne.net/common/main.js"></script>
</body>
</html>