<?php
	// Start session.
	session_start();

	// Check if user is logged.
	require_once("user/login/isLogged.php");
	
	// Get database variables.
	require_once("connect.php");
	
	// Set flag to see more details about errors.
	mysqli_report(MYSQLI_REPORT_STRICT);
	
	// Create connection
	$connection = @new mysqli($host, $db_user, $db_password, $db_name);
	
	// Calculate for chart.
	if($connection->connect_errno == 0)
	{
		$sql = "SELECT * FROM bugs";
		$records = $connection->query($sql);
		
		// Counters.
		$resolvedCounter = 0;
		$pendingCounter = 0;
		$unresolvedCounter = 0;
		
		while($row=$records->fetch_assoc())
		{
			if($row['resolution'] == "Fixed" || $row['resolution'] == "Implemented" || $row['resolution'] == "Revised")
				++$resolvedCounter;
			else if($row['resolution'] == "In Development")	++$pendingCounter;
			else 											++$unresolvedCounter;
		}
		
		$records->free_result();
	}
	else
		die("Could not connect: ".mysql_error());
	
	require_once("common/head.php");
?>
	
	<?php require_once("common/navbar-b.php"); ?>	<!-- NAVBAR BEGGINING -->
	<li><a class="btn-floating btn-medium pulse indigo lighten-1" href="index.php"><i class="material-icons">stay_primary_portrait</i></a></li>
	<?php
		echo "<li><a class='btn blue-grey darken-1 japokki-white' href='bugs/index.php'";
		if($_SESSION['permissions'] == "user")	echo " disabled ";
		echo '><i class="material-icons right">bug_report</i>Bugs</a></li>';
	?>
	<?php require_once("common/navbar-e.php"); ?>	<!-- NAVBAR END -->
	<?php require_once("common/sidenav-b.php"); ?>	<!-- SIDENAV BEGGINING -->
	<li><a href="index.php" class="japokki-black"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
	<?php
		echo '<li><a href="bugs/index.php" class="japokki-black';
		if($_SESSION['permissions'] == "user")
			echo " disabled";
		echo '"><i class="material-icons">bug_report</i>Bugs</a></li>';
	?>
	<?php require_once("common/sidenav-e.php"); ?>	<!-- SIDENAV END -->
	
	
	<div class="container center">
		
		<!-- chart -->
		<canvas id="myChart" style="height: 370px; width: 100%;"></canvas>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.4.0/Chart.min.js"></script>
		<div class="service-con" data-service="<?php echo 40; ?>"></div>
		<script>
			var js_resolved =	<?php echo json_encode($resolvedCounter); ?>;
			var js_pending =	<?php echo json_encode($pendingCounter); ?>;
			var js_unresolved =	<?php echo json_encode($unresolvedCounter); ?>;
			
			var ctx = document.getElementById('myChart').getContext('2d');
			var chart = new Chart(ctx, {
				
				type: 'line',

				// The data for our dataset
				data: {
					labels: ["Resolved", "Pending", "Unresolved"],
					datasets:
					[	{label: "Resolved",
						backgroundColor: '#66BB6A',
						borderColor: '#66BB6A',
						data: [js_resolved, 0, 0]},
						
						{label: "Pending",
						backgroundColor: '#FFCA28',
						borderColor: '#FFCA28',
						data: [0, js_pending, 0],},
						
						{label: "Unresolved",
						backgroundColor: '#EF5350',
						borderColor: '#EF5350',
						data: [0, 0, -js_unresolved]},
					]
				},
				
				options: {
					title: {
						display: true,
						text: "Combat Halloween Bugs",
						fontFamily: "japokki",
						fontSize: 25
					},
					
					legend: {
						labels: {
							fontFamily: "japokki"
						}
					},
					
					scales: {
						yAxes: [{
								ticks: {
									fontFamily: "japokki"
								}
						}],
						xAxes: [{
								ticks: {
									fontFamily: "japokki"
								}
						}]
					}
				}
			});
		</script>
		<!-- ---------------------------------- -->
		
		
		
	</div>
	
<?php require_once("common/footer.php"); ?>