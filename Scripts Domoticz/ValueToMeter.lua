------------------------------------------------------------------------------
-- Raw counter sensor
pulse_counter = 'Meter pulse counter'
 
-- Electric meter virtual sensor
meter_name = 'Electric meter'
meter_id = 29
 
-- User variable containing the counter zero point (Wh)
meter_base = 'Meter pulse start'


-- Needs update

------------------------------------------------------------------------------
commandArray = {}
 
if (devicechanged[pulse_counter]) then
   pulses = tonumber(otherdevices_svalues[pulse_counter])
   prev_meter = tonumber(otherdevices_svalues[meter_name])
 
   base = tonumber(uservariables[meter_base])
   if (base + pulses < prev_meter) then
     -- Pulse counter seems to have been reset.
     print('Pulse count reset; updating base from ' .. base .. ' to ' .. prev_meter)
     base = prev_meter
     commandArray['Variable:' .. meter_base] = tostring(base)
   end
-- print('Meter reading ' .. base .. ' + ' .. pulses .. ' = ' .. base + pulses)
   commandArray['UpdateDevice'] = meter_id .. "|0|" .. base + pulses
end
 
return commandArray