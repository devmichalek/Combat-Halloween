<!-- FIXED BUTTON - DOC AND PROFILE -->
<?php
    if(isset($_SESSION['logged']))
    {
        echo '<div class="fixed-action-btn horizontal click-to-toggle">';
        echo '<a class="btn-floating pulse btn-large red lighten-1"><i class="large material-icons">attach_file</i></a>';
        echo '<ul>';
        echo '<li><a class="btn-floating pulse amber lighten-1" href="https://amichalek.pl/combathalloween/other/commands.php" data-target="mobile-demo"><i class="material-icons">receipt</i></a></li>';
        echo '<li><a class="btn-floating red lighten-1';
        if($_SESSION['permissions'] == "user")  echo " disabled ";
        else                                    echo " pulse ";
        echo '" href="https://amichalek.pl/combathalloween/bugs/other/documentation.php"><i class="material-icons">insert_chart</i></a></li>';
        echo '<li><a class="btn-floating pulse blue-grey darken-1 sidenav-trigger" href="#" data-target="mobile-demo"><i class="material-icons">person</i></a></li>';
        echo '</ul>';
        echo '</div>';
    }
?>
</main>

<!-- Footer -->
<footer class="page-footer bg-black japokki-white">
    <div class="container">
    <div class="row center">
        <div class="col s12 m3">
            <h5>Code & Structure:</h5>
            <div class="chip"><img src="https://amichalek.pl/combathalloween/images/users/devmichalek@gmail.com.jpg" alt="Contact Person">Adrian Michałek</div><br>
            <div class="chip">devmichalek@gmail.com<i class="close material-icons">close</i></div>
        </div>
        <div class="col s12 m3">
            <h5>Support:</h5>
            <div class="chip"><img src="https://amichalek.pl/combathalloween/images/users/sebastek321@gmail.com.jpg" alt="Contact Person">Sebastian Bialucha</div><br>
            <div class="chip">sebastek321@gmail.com<i class="close material-icons">close</i></div>
            <div class="chip"><img src="https://amichalek.pl/combathalloween/images/users/kamilgawlik@icloud.com.jpg" alt="Contact Person">Kamil Gawlik</div><br>
            <div class="chip">kamilgawlik@icloud.com<i class="close material-icons">close</i></div>
        </div>
        <div class="col s12 m6">
            <h5>Project Structure:</h5>
            <p class="grey-text text-lighten-4">The website based on Materialize and Chart.js, some PHP & SQL code and mostly HTML & CSS & JS. The game was made with C++ language (C++14 standard) and SFML. Map editor was written with QT modules like Network, Window or Graphics. The whole project "Combat Halloween" was developed with Agile Software Development & SWOT approach.</p>
        </div>
    </div>
    <div class="footer-copyright col s12 m4">
    <a class="modal-trigger waves-effect waves-light btn blue-grey darken-1" href="#license">©2018 Terms of Use</a>
    </div>
  </div>
</footer>

  <!-- LICENSE -->
<div id="license" class="modal modal-fixed-footer japokki-black">
  <div class="modal-content">
    <h4>MIT License</h4>
    <div><p ><?php require_once('LICENSE.txt'); ?></p></div>
  </div>
  <div class="modal-footer">
    <a href="#!" class="modal-action modal-close waves-effect waves-green btn-flat japokki-black">Agree</a>
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
<script type="text/javascript" src="https://amichalek.pl/combathalloween/common/main.js"></script>
</body>
</html>