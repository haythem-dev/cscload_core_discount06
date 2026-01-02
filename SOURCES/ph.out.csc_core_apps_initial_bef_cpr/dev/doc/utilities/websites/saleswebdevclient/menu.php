<html>

<head>
    <title>menu</title>
    <base target="main">
    <link rel="stylesheet" type="text/css" href="style/prz.css"/>

    <script language="JavaScript" type="text/javascript">
    <!-- //

		function outline(id)
		{
			if( document.getElementById(id).style.display == 'none' )
			{
				document.getElementById(id).style.display = 'block';
			}
			else
			{
				document.getElementById(id).style.display = 'none';
			}

			if(id!='menu_schweiz')     {document.getElementById('menu_schweiz').style.display='none';}
			if(id!='menu_kroatien')    {document.getElementById('menu_kroatien').style.display='none';}
			if(id!='menu_serbien')     {document.getElementById('menu_serbien').style.display='none';}
			if(id!='menu_frankreich')  {document.getElementById('menu_frankreich').style.display='none';}
			if(id!='menu_deutschland') {document.getElementById('menu_deutschland').style.display='none';}
			if(id!='menu_oesterreich') {document.getElementById('menu_oesterreich').style.display='none';}
			if(id!='menu_bulgaria')    {document.getElementById('menu_bulgaria').style.display='none';}
		}

		function outline2(id)
		{
			if( document.getElementById(id).style.display == 'none' )
			{
				document.getElementById(id).style.display = 'block';
			}
			else
			{
				document.getElementById(id).style.display = 'none';
			}

			if(id!='interfaces_schweiz')     {document.getElementById('interfaces_schweiz').style.display='none';}
			if(id!='interfaces_kroatien')    {document.getElementById('interfaces_kroatien').style.display='none';}
			if(id!='interfaces_serbien')     {document.getElementById('interfaces_serbien').style.display='none';}
			if(id!='interfaces_frankreich')  {document.getElementById('interfaces_frankreich').style.display='none';}
			if(id!='interfaces_deutschland') {document.getElementById('interfaces_deutschland').style.display='none';}
			if(id!='interfaces_oesterreich') {document.getElementById('interfaces_oesterreich').style.display='none';}
			if(id!='interfaces_bulgaria')    {document.getElementById('interfaces_bulgaria').style.display='none';}
		}

	// -->
	</script>

</head>

<body alink="#000000" vlink="#000000" link="#000000">
<h1>SalesWeb</h1>
<table width="100%" cellpadding="0" cellspacing="0"  rules="cols" style="font-size: 10pt">


	<!-- Österreich -->
		<tr>
			<th>
				<img src="images/small_oesterreich.gif" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_oesterreich'); return false;" target="menu">
					<font color='White'>Austria</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_oesterreich" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_oesterreich'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_oesterreich" style="display:none">
					    <img src="images/simplearrow.gif"/> <a href="oesterreich/argeinfo.php"> ArgeInfo </a><br/>
					    <img src="images/simplearrow.gif"/> <a href="oesterreich/argeorder.php"> ArgeOrder </a><br/>						
					</span>
				</span>
			</td>
		</tr>
		
	<!-- Bulgaria -->
		<tr>
			<th>
				<img src="images/small_bulgaria.jpg" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_bulgaria');return false;" target="menu">
					<font color="White">Bulgaria</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_bulgaria" style="display:none">
					<img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_bulgaria'); return false;" target="menu">
						<b>Interfaces</b>
					</a>					
					<span id="interfaces_bulgaria" style="display:none">					
						<img src="images/simplearrow.gif"/> <a href="bulgaria/articlelist.php"> ArticleList </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/changedquantities.php"> ChangedQuantities </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/creditlimit.php"> CreditLimit </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/discountaccount.php"> DiscountAccount </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/expirydates.php"> ExpiryDates </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/invoices.php"> Invoices </a><br/>
						<img src="images/simplearrow.gif"/> <a href="bulgaria/order.php"> Order </a><br/>								
						<img src="images/simplearrow.gif"/> <a href="bulgaria/orderstatus.php"> OrderStatus </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/paymentconditions.php"> PaymentConditions </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/payments.php"> Payments </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/pricesanddiscounts.php"> PricesAndDiscounts </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/pricesanddiscounts2.php"> PricesAndDiscounts2 </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/productavailability.php"> ProductAvailability </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/promotions.php"> Promotions </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/routes.php"> Routes </a><br />				
						<img src="images/simplearrow.gif"/> <a href="bulgaria/substitutes.php"> Substitutes </a><br />
						<img src="images/simplearrow.gif"/> <a href="bulgaria/turnover.php"> Turnover </a><br />						
					</span>
				</span>
			</td>
		</tr>
		

	<!-- Kroatien -->
		<tr>
			<th>
				<img src="images/small_kroatien.gif" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_kroatien'); return false;" target="menu">
					<font color='White'>Croatia</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_kroatien" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_kroatien'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_kroatien" style="display:none">
						<img src="images/simplearrow.gif"/> <a href="kroatien/articlecatalogue.php"> Article Catalogue </a><br/>
						<img src="images/simplearrow.gif"/> <a href="kroatien/invoice.php"> Invoice </a><br/>
						<img src="images/simplearrow.gif"/> <a href="kroatien/order.php"> Order </a><br/>						
					</span>
				</span>
			</td>
		</tr>	
		
	<!-- Serbien -->
		<tr>
			<th>
				<img src="images/small_serbia.jpg" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_serbien'); return false;" target="menu">
					<font color='White'>Serbia</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_serbien" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_serbien'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_serbien" style="display:none">
						<img src="images/simplearrow.gif"/> <a href="serbien/articlecatalogue.php"> Article Catalogue </a><br/>						
						<img src="images/simplearrow.gif"/> <a href="serbien/creditlimit.php"> CreditLimit </a><br />
						<img src="images/simplearrow.gif"/> <a href="serbien/deliverylist.php"> DeliveryList </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/order.php"> Order </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/orderinfo.php"> OrderInfo </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/pharmacies.php"> Pharmacies </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/prices.php"> Prices </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/products.php"> Products </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/stocklevel.php"> StockLevel </a><br/>
						<img src="images/simplearrow.gif"/> <a href="serbien/tenderinfo.php"> TenderInfo </a><br/>
					</span>
				</span>
			</td>
		</tr>			
	

	<!-- Frankreich -->
		<tr>
			<th>
				<img src="images/small_frankreich.gif" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_frankreich'); return false;" target="menu">
					<font color='White'>France</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_frankreich" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_frankreich'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_frankreich" style="display:none">
					    <img src="images/simplearrow.gif"/> <a href="frankreich/articlecatalogue.php"> ArticleCatalogue </a><br/>
					    <img src="images/simplearrow.gif"/> <a href="frankreich/deliverynote.php"> Deliverynotes </a><br/>
					    <img src="images/simplearrow.gif"/> <a href="frankreich/order.php"> Order </a><br/>						
					</span>
				</span>
			</td>
		</tr>			

	<!-- Deutschland -->
		<tr>
			<th>
				<img src="images/small_deutschland.gif" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_deutschland'); return false;" target="menu">
					<font color='White'>Germany</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_deutschland" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_deutschland'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_deutschland" style="display:none">
						<img src="images/simplearrow.gif"/> <a href="deutschland/articlecatalogue.php"> Article Catalogue </a><br/>
						<img src="images/simplearrow.gif"/> <a href="deutschland/invoice.php"> Invoice </a><br/>
						<img src="images/simplearrow.gif"/> <a href="deutschland/order.php"> Order </a><br/>						
						<img src="images/simplearrow.gif"/> <a href="deutschland/stocklevel.php"> Stocklevel </a><br/>						
					</span>
				</span>
			</td>
		</tr>


	<!-- Schweiz -->
		<tr>
			<th>
				<img src="images/small_schweiz.gif" height="17" width="28"/>
			</th>
			<th align="left">
				&nbsp;
				<a href="#" onclick="outline('menu_schweiz'); return false;" target="menu">
					<font color='White'>Switzerland</font>
				</a>
			</th>
		</tr>
		<tr>
			<td colspan="2" valign="middle">
				<span id="menu_schweiz" style="display:none">
				    <img src="images/icon.gif"/>
					<a href="#" onclick="outline2('interfaces_schweiz'); return false;" target="menu">
						<b>Interfaces</b>
					</a>
					<span id="interfaces_schweiz" style="display:none">
						<img src="images/simplearrow.gif"/> <a href="schweiz/cucos.php"> CuCos </a> <br/>
						<img src="images/simplearrow.gif"/> <a href="schweiz/deliverynote.php"> Delivery Note </a> <br/>
						<img src="images/simplearrow.gif"/> <a href="schweiz/order.php"> Order </a> <br/>
						<img src="images/simplearrow.gif"/> <a href="schweiz/productavailability.php"> Product Availability </a> <br/>						
					</span>
				</span>
			</td>
		</tr>

</table>


</body>

</html>
