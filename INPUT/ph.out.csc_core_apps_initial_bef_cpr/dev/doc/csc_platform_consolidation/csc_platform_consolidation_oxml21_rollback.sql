--------------------------------------------
-- To be used on OXML21                   --
-- Replace <?F> with the correct branchno --
--------------------------------------------

UPDATE ode21@ode21s_oxml21_tcp:rechner 
	SET datenbank_name='ode22@ode22s_oxml21_tcp' WHERE filialnr=<?F>;
	
UPDATE ode22@ode22s_oxml21_tcp:rechner 
	SET datenbank_name='ode22@ode22s_oxml21_tcp' WHERE filialnr=<?F>;
	