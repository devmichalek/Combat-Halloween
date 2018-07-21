<?php

  // Start session.
  session_start();

  // Check if user is logged.
  require_once("../user/isLogged.php");

  // Check if user has admin permissions.
  require_once("../user/isAdmin.php");

  if($connection->connect_errno == 0)
  {
    $sql = "SELECT * FROM bugs";
    $records = $connection->query($sql);

    $sumnum = 0;
    $donenum = 0;
    $opennum = 0;
    while($row=$records->fetch_assoc())
    {
      ++$sumnum;
      if($row['resolution'] == "Fixed" || $row['resolution'] == "Implemented" || $row['resolution'] == "Revised")
        ++$donenum;
      else
        ++$opennum;
    }
    $records->free_result();

    // Set resolution and developer select.
    $rselect = "unresolved";
    $dselect = "mine";
    if(isset($_GET['rselect']))  $rselect = $_GET['rselect'];
    if(isset($_GET['dselect']))  $dselect = $_GET['dselect'];
    
    $rresult = "WHERE 1";
    if($rselect == "finished")        $rresult = "WHERE resolution IN ('fixed', 'revised', 'implemented')";
    else if($rselect == "unresolved") $rresult = "WHERE NOT resolution IN ('fixed', 'revised', 'implemented')";

    $dresult = " AND 1";
    if($dselect == "mine")        $dresult = " AND developer='".$_SESSION['email']."'";
    else if($dselect == "their")  $dresult = " AND NOT developer='".$_SESSION['email']."'";
    
    $records = $connection->query("SELECT * FROM bugs ".$rresult.$dresult);
    $isempty = empty($records);
  }
  else
  {
    die("Could not connect: ".mysql_error());
  }
  
    require_once("../head.php");
?>
    <!-- NAVBAR -->
    <nav>
    <div class="nav-wrapper">
        <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
                <li><a class="btn-floating btn-medium pulse deep-orange lighten-1" href="modules.php"><i class="material-icons">view_module</i></a></li>
                <li><a class="btn-floating btn-medium pulse indigo lighten-1" href="documentation.php"><i class="material-icons">info_outline</i></a></li>
                <li><a class="nav btn amber lighten-1 nav-button" href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download">Sprite Tester</a></li>
                <li><a class="nav btn red lighten-1 nav-button" href="addbug.php"><i class="material-icons right">bug_report</i>Add</a></li>
            </ul>
        </div>
    </div>
    </nav>
    <ul class="nav-main sidenav" id="mobile-demo">
        <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
        <li><a class="btn-floating btn-medium pulse deep-orange lighten-1" href="modules.php"><i class="material-icons">view_module</i></a></li>
        <li><a class="btn-floating btn-medium pulse indigo lighten-1" href="documentation.php"><i class="material-icons">info_outline</i></a></li>
        <li><a class="nav btn amber lighten-1 nav-button" href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download">Sprite Tester</a></li>
        <li><a class="nav btn red lighten-1 nav-button" href="addbug.php"><i class="material-icons right">bug_report</i>Add</a></li>
    </ul>
    <!-- END OF NAVBAR -->

  <div class="container center">
    <div class="row">
      <h2 class="center">Combat Halloween Bugs</h2>
      <h4 class="modcon">Finished: <?php echo $donenum;?> Unresolved: <?php echo $opennum;?> All: <?php echo $sumnum;?></h4>
      
      <!-- SORT BY-->
        <form action="index.php" method="get">
          <div class="row">
            <div class="input-field col s6 m3 push-m3">
            <select name="rselect">
                <?php
                echo "<option "; if($rselect=="all")   echo " selected "; echo 'value="all">All</option>';
                echo "<option "; if($rselect=="finished")   echo " selected "; echo 'value="finished">Finished</option>';
                echo "<option "; if($rselect=="unresolved")   echo " selected "; echo 'value="unresolved">Unresolved</option>';
                ?>
            </select>
                <label>Sort by resolution</label>
            </div>
            
            <div class="input-field col s6 m3 push-m3">
            <select name="dselect">
                <?php
                echo "<option "; if($dselect=="all")   echo " selected "; echo 'value="all">All</option>';
                echo "<option "; if($dselect=="mine")   echo " selected "; echo 'value="mine">Mine</option>';
                echo "<option "; if($dselect=="their")   echo " selected "; echo 'value="their">Their</option>';
                ?>
            </select>
                <label>Sort by developer</label>
            </div>
          </div>

            <div class="center col s8 m4 push-m4 push-s2">
            <button class="waves-effect waves-light btn green lighten-1 japokki" type="submit"><i class="material-icons right">redo</i>Reload </button>
            </div>
        </form>
        
      <!-- ------ -->
      
      <div class="center col s12">
        <table class="striped centered responsive-table bordered">
              <thead class="tableheader">
                <tr>
                    <?php
                    if(!$isempty)
                    {
                        echo "<th>Name</th>";
                        echo "<th>Type</th>";
                        echo "<th>Description</th>";
                        echo "<th>Location</th>";
                        echo "<th>Severity</th>";
                        echo "<th>Priority</th>";
                        echo "<th>Deadline</th>";
                        echo "<th>Resolution</th>";
                    }
                    ?>
                </tr>
              </thead>
          <tbody class="member">
          
          <?php

            while($row=$records->fetch_assoc())
            {
              echo "<tr>";
              
              // Color
              $color = "''";
              $resolution = $row['resolution'];
              if($resolution == "Fixed" ||
                 $resolution == "Revised" ||
                 $resolution == "Implemented")
              $color = "'grey lighten-2'";
              
              // Name
              echo "<td class=".$color.">";
              echo '<form action="editbug.php" method="get">';
              echo $row['name'];
              echo '<input type="hidden" name="IDname" value="';
              echo $row['IDname'].'"> ';
              $descolor = ltrim($color, "'");
              if($descolor == "")
                  $descolor = "cyan lighten-1'";
              echo "<button type='submit' class='btn-floating ".$descolor."><i class='material-icons'>edit</i></button>";
              echo '</form>'."</td>";

              // Type
              $type = $row['type'];
              if($color == "''")
              {
                  switch($type)
                  {
                      case "Bug":             echo "<td class='red lighten-1'>".$type."</td>";   break;
                      case "Change":          echo "<td class='amber lighten-1'>".$type."</td>"; break;
                      case "New Feature":     echo "<td class='green lighten-1'>".$type."</td>"; break;
                      case "Syntax Error":    echo "<td class='red lighten-1'>".$type."</td>";   break;
                      default:                echo "<td class='grey lighten-1'>".$type."</td>";  break;
                  }
              }
              else
                  echo "<td class=".$color.">".$type."</td>";

              // Description (button + form)
              echo "<td class=".$color.">";
              $descolor = ltrim($color, "'");
              
              if($descolor == "")
              {
                  $descolor = "'";
                  if($row['developer'] == $_SESSION['email'])
                      $descolor = "red lighten-1'";
                  
              }
              
                echo "<a class='waves-effect waves-light btn modal-trigger ".$descolor." ";
                echo "href='#".$row['name']."'>";
                echo "Info</a></td>";
                echo "<div id='".$row['name']."' class='modal'>";
                echo "<div class='modal-content'>";
                echo "<h4 class='modcon'>".$row['name']." ID(".$row['IDname'].")</h4>";
                echo "<p class='japokki'>Reported by:  ".'<img style="position: relative; top: 10px;" src="../images/'.$row['author'].'.jpg" class="circle"> '.$row['author']."</p>";
                echo "<p class='japokki'>Developer:  ".'<img style="position: relative; top: 10px;" src="../images/'.$row['developer'].'.jpg" class="circle"> '.$row['developer']."</p>";
                echo "<p class='japokki'>Action to do: ".$row['action']."</p>";
                echo "<p class='japokki'>".$row['description']."</p>";
                echo "</div>";
                echo '<div class="modal-footer">';
                echo '<a href="#!" class="modal-close waves-effect waves-green btn-flat japokki">Ok</a>';
                echo "</div>";
                echo "</div>";

                // Location - link
                $location = $row['location'];
                echo "<td class=".$color.">";
                if($location == "None")
                  echo "None</td>";
                else
                    echo "<a target='_blank' href='".$location."'>Link</a></td>";
              
              // Severity
              $severity = $row['severity'];
              if($color == "''")
                  switch($severity)
                  {
                      case "Fatal":   echo "<td class='deep-purple'>";    break;
                      case "Serious": echo "<td class='red lighten-1'>";  break;
                      default:        echo "<td class='grey lighten-1'>"; break;
                  }
              else
                  echo "<td class=".$color.">";
              echo $severity."</td>";
              
              // Priority
              $priority = $row['priority'];
              if($color == "''")
                  switch($priority)
                  {
                      case "Must Do":   echo "<td class='deep-purple'>";    break;
                      case "Medium": echo "<td class='orange lighten-1'>";  break;
                      case "High": echo "<td class='red lighten-1'>";  break;
                      default:        echo "<td class='grey lighten-1'>"; break;
                  }
                else
                    echo "<td class=".$color.">";
              echo $priority."</td>";

              // Deadline
              $deadline = $row['deadline'];
              if($color == "''")
              {
                  if($deadline != "Not scheduled")  echo "<td class='red lighten-1'>";
                  else                echo "<td class='grey lighten-1'>";
              }
              else
                  echo "<td class=".$color.">";
              echo $deadline."</td>";

              // Resolution
              switch($resolution)
              {
                  case "Deferred":                    echo "<td class='red lighten-1'>";          break;
                  case "Disagree":                    echo "<td class='pink lighten-1'>";         break;
                  case "Duplicated":                  echo "<td class='red lighten-1'>";          break;
                  case "Fixed":                       echo "<td class='green lighten-1'>";        break;
                  case "Hold":                        echo "<td class='red lighten-1'>";          break;
                  case "Implemented":                 echo "<td class='green lighten-1'>";        break;
                  case "In Development":              echo "<td class='amber lighten-1'>";        break;
                  case "Known Problem":               echo "<td class='red lighten-1'>";          break;
                  case "Need More Info":              echo "<td class='pink lighten-1'>";         break;
                  case "New":                         echo "<td class='red lighten-1'>";          break;
                  case "Obsolete":                    echo "<td class='red lighten-1'>";          break;
                  case "Reeopen":                     echo "<td class='red lighten-1'>";          break;
                  case "Revised":                     echo "<td class='green lighten-1'>";        break;
                  case "Not To Correct":              echo "<td class='pink lighten-1'>";         break;
                  case "Support Needed":              echo "<td class='pink lighten-1'>";         break;
                  case "Withdrawn":                   echo "<td class='pink lighten-1'>";         break;
                  default:                            echo "<td class='grey lighten-1'>";         break;
              }
              echo $resolution."</td>";
                            
                            // End
              echo "</tr>";
            }

            $records->free_result()
          ?>
          </tbody>
        </table>
      </div>
    </div>
  </div>

<?php require_once("../footer.php"); ?>